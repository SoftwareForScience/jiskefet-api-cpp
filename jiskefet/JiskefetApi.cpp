#include "JiskefetApi.h"
#include <algorithm>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/time_parsers.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <cpprest/json.h>
#include "FlpApi.h"
#include "LogsApi.h"
#include "RunsApi.h"


namespace jiskefet
{

namespace
{
std::string orderDirectionToString(OrderDirection orderDirection) {
    switch (orderDirection) {
        case OrderDirection::ASC: return "ASC";
        case OrderDirection::DESC: return "DESC";
        default: throw std::runtime_error("Unknown OrderDirection enum value");
    }    
}

std::string logSubtypeToString(LogSubtype logSubtype) {
    switch (logSubtype) {
        case LogSubtype::RUN: return "run";
        case LogSubtype::SUBSYSTEM: return "subsystem";
        case LogSubtype::ANNOUNCEMENT: return "announcement";
        case LogSubtype::INTERVENTION: return "intervention";
        case LogSubtype::COMMENT: return "comment";
        default: throw std::runtime_error("Unknown LogSubtype enum value");
    }
}

std::string logOriginToString(LogOrigin logOrigin) {
    switch (logOrigin) {
        case LogOrigin::HUMAN: return "human";
        case LogOrigin::PROCESS: return "process";
        default: throw std::runtime_error("Unknown LogOrigin enum value");
    }
}

std::string runTypeToString(RunType runType) {
    switch (runType) {
        case RunType::PHYSICS: return "PHYSICS";
        case RunType::COSMICS: return "COSMICS";
        case RunType::TECHNICAL: return "TECHNICAL";
        default: throw std::runtime_error("Unknown RunType enum value");
    }    
}

std::string runQualityToString(RunQuality runQuality) {
    switch (runQuality) {
        case RunQuality::GOOD: return "GOOD";
        case RunQuality::BAD: return "BAD";
        case RunQuality::UNKNOWN: return "UNKNOWN";
        default: throw std::runtime_error("Unknown RunQuality enum value");
    }    
}


utility::datetime ptimeToDateTime(boost::posix_time::ptime t)
{
    return utility::datetime::from_string(boost::posix_time::to_iso_extended_string(t), utility::datetime::ISO_8601);
};

boost::posix_time::ptime datetimeToPtime(utility::datetime t)
{
    return boost::posix_time::from_iso_extended_string(t.to_string(utility::datetime::ISO_8601));
}

boost::posix_time::ptime ptimeFromString(std::string t)
{
    // Boost doesn't like the Z at the end..
    if (!t.empty() && (t.back() == 'Z')) {
        t.pop_back();
    }
    return boost::posix_time::from_iso_extended_string(t);
}
}

JiskefetApi::JiskefetApi(std::string url, std::string token)
{
    apiClient = std::make_shared<io::swagger::client::api::ApiClient>();
    auto apiConfiguration = std::make_shared<io::swagger::client::api::ApiConfiguration>();
    apiConfiguration->setBaseUrl(url);
    apiConfiguration->setApiKey("Authorization", " Bearer " + token);
    apiConfiguration->setUserAgent("JiskefetCppApi");
    apiClient->setConfiguration(apiConfiguration);
}

void JiskefetApi::runStart(int64_t runNumber, boost::posix_time::ptime o2Start,
      boost::posix_time::ptime triggerStart, std::string activityId, 
      RunType runType, int64_t nDetectors, int64_t nFlps, int64_t nEpns) 
{
    io::swagger::client::api::RunsApi runsApi(apiClient);
    auto dto = std::make_shared<io::swagger::client::model::CreateRunDto>();
    dto->setRunNumber(runNumber);
    dto->setO2StartTime(ptimeToDateTime(o2Start));
    dto->setTrgStartTime(ptimeToDateTime(triggerStart));
    dto->setRunType(runTypeToString(runType));
    dto->setActivityId(activityId);
    dto->setNDetectors(nDetectors);
    dto->setNFlps(nFlps);
    dto->setNEpns(nEpns);
    runsApi.runsPost(dto).get();
}

void JiskefetApi::runEnd(int64_t runNumber, boost::posix_time::ptime o2End, boost::posix_time::ptime triggerEnd,
      RunQuality runQuality)
{
    io::swagger::client::api::RunsApi runsApi(apiClient);
    auto dto = std::make_shared<io::swagger::client::model::PatchRunDto>();
    dto->setO2EndTime(ptimeToDateTime(o2End));
    dto->setTrgEndTime(ptimeToDateTime(triggerEnd));
    dto->setRunQuality(runQualityToString(runQuality));
    runsApi.runsIdPatch(dto, runNumber);
}

void JiskefetApi::flpAdd(int64_t runNumber, std::string flpName, std::string hostName)
{
    io::swagger::client::api::FlpApi flpApi(apiClient);
    auto dto = std::make_shared<io::swagger::client::model::CreateFlpDto>();
    dto->setRun(runNumber);
    dto->setFlpName(flpName);
    dto->setFlpHostname(hostName);
    flpApi.flpPost(dto);
}

void JiskefetApi::flpUpdateCounters(int64_t runNumber, std::string flpName, int64_t nSubtimeframes, int64_t nEquipmentBytes,
      int64_t nRecordingBytes, int64_t nFairMqBytes)
{
    io::swagger::client::api::FlpApi flpApi(apiClient);
    auto dto = std::make_shared<io::swagger::client::model::PatchFlpDto>();
    dto->setEquipmentBytes(nEquipmentBytes);
    dto->setFairMQBytes(nFairMqBytes);
    dto->setNSubTimeframes(nSubtimeframes);
    dto->setRecordingBytes(nRecordingBytes);
    flpApi.flpNameRunsIdPatch(dto, flpName, runNumber);
}

std::vector<Run> JiskefetApi::getRuns(const GetRunsParameters& params)
{
    io::swagger::client::api::RunsApi runsApi(apiClient);
    auto emptyString = boost::optional<std::string>();
    auto emptyTime = boost::optional<utility::datetime>();

    pplx::task<std::shared_ptr<io::swagger::client::model::Object>> taskRunsGet = runsApi.runsGet(
        params.orderBy,
        params.orderDirection ? orderDirectionToString(*params.orderDirection) : emptyString,
        params.pageSize ? std::to_string(*params.pageSize) : emptyString,
        params.pageNumber ? std::to_string(*params.pageNumber) : emptyString,
        params.runNumber ? std::to_string(*params.runNumber) : emptyString,
        params.startTimeO2Start ? ptimeToDateTime(*params.startTimeO2Start) : emptyTime,
        params.endTimeO2Start ? ptimeToDateTime(*params.endTimeO2Start) : emptyTime,
        params.startTimeTrgStart ? ptimeToDateTime(*params.startTimeTrgStart) : emptyTime,
        params.endTimeTrgStart ? ptimeToDateTime(*params.endTimeTrgStart) : emptyTime,
        params.startTimeTrgEnd ? ptimeToDateTime(*params.startTimeTrgEnd) : emptyTime,
        params.endTimeTrgEnd ? ptimeToDateTime(*params.endTimeTrgEnd) : emptyTime,
        params.startTimeO2End ? ptimeToDateTime(*params.startTimeO2End) : emptyTime,
        params.endTimeO2End ? ptimeToDateTime(*params.endTimeO2End) : emptyTime,
        params.activityId,
        params.runType ? runTypeToString(*params.runType) : emptyString,
        params.runQuality ? runQualityToString(*params.runQuality) : emptyString);

    std::shared_ptr<io::swagger::client::model::Object> result = taskRunsGet.get();

    std::vector<Run> runs;
    auto runsJson = result->getValue("runs").as_array();
    for (const auto& item : runsJson) {
        const auto& runJson = item.as_object();
        Run run;
        run.runNumber = runJson.at("runNumber").as_number().to_int64();
        run.timeO2Start = ptimeFromString(runJson.at("timeO2Start").as_string());
        run.timeTrgStart = ptimeFromString(runJson.at("timeTrgStart").as_string());
        run.timeO2End = ptimeFromString(runJson.at("timeO2End").as_string());
        run.timeTrgEnd = ptimeFromString(runJson.at("timeTrgEnd").as_string());
        run.runType = runJson.at("runType").as_string();
        run.runQuality = runJson.at("runQuality").as_string();
        run.activityId = runJson.at("activityId").as_string();
        run.nDetectors = runJson.at("nDetectors").as_number().to_int64();
        run.nFlps = runJson.at("nFlps").as_number().to_int64();
        run.nEpns = runJson.at("nEpns").as_number().to_int64();
        run.nTimeframes = runJson.at("nTimeframes").as_number().to_int64();
        run.nSubtimeframes = runJson.at("nSubtimeframes").as_number().to_int64();
        run.bytesReadOut = runJson.at("bytesReadOut").as_number().to_int64();
        run.bytesTimeframeBuilder = runJson.at("bytesTimeframeBuilder").as_number().to_int64();
        runs.push_back(run);
    }
    return runs;
}

void JiskefetApi::createLog(const CreateLogParameters& params)
{
    io::swagger::client::api::LogsApi api(apiClient);
    auto dto = std::make_shared<io::swagger::client::model::CreateLogDto>();
    dto->setSubtype(logSubtypeToString(params.subtype));
    dto->setOrigin(logOriginToString(params.origin));
    dto->setTitle(params.title);
    dto->setBody(params.text);

    // Not sure how this works...
    //dto->setAttachments(???); 
    if (params.attachments.size() != 0) {
        throw std::runtime_error("JiskefetApi::createLog() attachments not yet supported");
    }
    
    // Convert ids from int to string
    std::vector<std::string> runIds;
    std::transform(params.runIds.begin(), params.runIds.end(), std::back_inserter(runIds), 
        [](int32_t x){return std::to_string(x);});
    dto->setRuns(runIds);

    std::shared_ptr<io::swagger::client::model::Object> result = api.logsPost(dto).get();
    // TODO check if result is OK and return log ID
}

std::vector<Log> JiskefetApi::getLogs(const GetLogsParameters& params)
{
    throw std::runtime_error("JiskefetApi::getLogs() not yet supported");
    return {};
}

}