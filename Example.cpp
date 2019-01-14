#include <string>
#include <iostream>
#include "ApiClient.h"
#include "api/RunsApi.h"
#include "boost/none.hpp"
#include "cpprest/oauth2.h"
#include "pplx/threadpool.h"

namespace 
{
    std::string getEnvString(const std::string& key)
    {
        char* env = std::getenv(key.c_str());
        return (env == nullptr) ? std::string("") : std::string(env);
    }

    struct Run
    {
        utility::datetime timeO2Start;
        utility::datetime timeTrgStart;
        utility::datetime timeO2End;
        utility::datetime timeTrgEnd;
        utility::string_t runType;
        utility::string_t runQuality;
        utility::string_t activityId;
        int32_t nDetectors;
        int32_t nFlps;
        int32_t nEpns;
        int32_t nTimeframes;
        int32_t nSubtimeframes;
        int32_t bytesReadOut;
        int32_t bytesTimeframeBuilder;
    };

    /// Example of how to convert the JSON object returned from RunsApi::runsGet() into regular C++ data structures.
    inline std::vector<Run> runsFromGetRunsResult(const std::shared_ptr<io::swagger::client::api::Object>& result) 
    {
        std::vector<Run> runs;
        auto runsJson = result->getValue("runs").as_array();
        for (const auto& item : runsJson) {
            const auto& runJson = item.as_object();
            Run run;
            run.timeO2Start = utility::datetime().from_string(runJson.at("timeO2Start").as_string());
            run.timeTrgStart = utility::datetime().from_string(runJson.at("timeTrgStart").as_string());
            run.timeO2End = utility::datetime().from_string(runJson.at("timeO2End").as_string());
            run.timeTrgEnd = utility::datetime().from_string(runJson.at("timeTrgEnd").as_string());
            run.runType = runJson.at("runType").as_string();
            run.runQuality = runJson.at("runQuality").as_string();
            run.activityId = runJson.at("activityId").as_string();
            run.nDetectors = runJson.at("nDetectors").as_integer();
            run.nFlps = runJson.at("nFlps").as_integer();
            run.nEpns = runJson.at("nEpns").as_integer();
            run.nTimeframes = runJson.at("nTimeframes").as_integer();
            run.nSubtimeframes = runJson.at("nSubtimeframes").as_integer();
            run.bytesReadOut = runJson.at("bytesReadOut").as_integer();
            run.bytesTimeframeBuilder = runJson.at("bytesTimeframeBuilder").as_integer();
            runs.push_back(run);
        }
        return runs;
    }
}


int main(int argc, char const *argv[])
{
    using namespace io;
    using namespace swagger;
    using namespace client;
    using namespace api;

    std::cout << "Hello jiskefet-api-cpp!" << std::endl;

	std::string hostUrl = getEnvString("JISKEFET_HOST");
	std::string apiPath = getEnvString("JISKEFET_PATH");
    std::string apiToken = getEnvString("JISKEFET_API_TOKEN");
    std::string baseUrl = "http://" + hostUrl + "/" + apiPath;

    std::cout << "JISKEFET_HOST:      " << hostUrl << '\n'
        << "JISKEFET_API_PATH:  " << apiPath << '\n'
        << "JISKEFET_API_TOKEN: " << apiToken << '\n';

    crossplat::threadpool::initialize_with_threads(1); // Optional, but it's generally not necessary to spawn 20+ threads
    auto apiClient = std::make_shared<ApiClient>();
    auto apiConfig = std::make_shared<ApiConfiguration>();
    apiConfig->setBaseUrl(baseUrl);
    apiConfig->setApiKey("Authorization", " Bearer " + apiToken);
    apiConfig->setUserAgent("JiskefetCppApi");
    apiClient->setConfiguration(apiConfig);
    RunsApi runsApi(apiClient);

    // Posts a run
    {
        std::cout << "Posting run\n";
        auto createRunDto = std::make_shared<model::CreateRunDto>();
        createRunDto->setTimeO2Start(utility::datetime().from_string("2018-11-26T16:43:22.279Z"));
        createRunDto->setTimeTrgStart(utility::datetime().from_string("2018-11-26T16:43:22.279Z"));
        createRunDto->setTimeO2End(utility::datetime().from_string("2018-11-26T16:43:22.279Z"));
        createRunDto->setTimeTrgEnd(utility::datetime().from_string("2018-11-26T16:43:22.279Z"));
        createRunDto->setRunType("my-run-type");
        createRunDto->setRunQuality("my-run-quality");
        createRunDto->setActivityId("cpp-api");
        createRunDto->setNDetectors(123);
        createRunDto->setNFlps(200);
        createRunDto->setNEpns(1000);
        createRunDto->setNTimeframes(12312);
        createRunDto->setNSubtimeframes(12312312);
        createRunDto->setBytesReadOut(1024*1024*1024);
        createRunDto->setBytesTimeframeBuilder(512*1024*1024);
        pplx::task<void> taskRunsPost = runsApi.runsPost(createRunDto);
        try {
            taskRunsPost.get();
        } catch(const std::exception& e) {
            std::cout << "runsPost() exception: " << e.what() << '\n';
        }
    }

    // Get runs
    {
        pplx::task<std::shared_ptr<Object>> taskRunsGet = runsApi.runsGet(
            boost::optional<utility::string_t>(), // orderBy,
            boost::optional<utility::string_t>(), // orderDirection,
            boost::optional<utility::string_t>(), // pageSize,
            boost::optional<utility::string_t>(), // pageNumber,
            boost::optional<utility::string_t>(), // runNumber,
            boost::optional<utility::datetime>(), // startTimeO2Start,
            boost::optional<utility::datetime>(), // endTimeO2Start,
            boost::optional<utility::datetime>(), // startTimeTrgStart,
            boost::optional<utility::datetime>(), // endTimeTrgStart,
            boost::optional<utility::datetime>(), // startTimeTrgEnd,
            boost::optional<utility::datetime>(), // endTimeTrgEnd,
            boost::optional<utility::datetime>(), // startTimeO2End,
            boost::optional<utility::datetime>(), // endTimeO2End,
            boost::optional<utility::string_t>(), // activityId,
            boost::optional<int32_t>(), // runType,
            boost::optional<int32_t>() // runQuality
        );
        std::shared_ptr<Object> result;
        try {
            result = taskRunsGet.get();
            std::cout << "Runs:\n" << result->toJson() << std::endl;
        } catch(const std::exception& e) {
            std::cout << "runsGet() exception: " << e.what() << '\n';
        }

        std::vector<Run> runs = runsFromGetRunsResult(result);
        std::cout << "Converted JSON:\n";
        for (const auto& run : runs) {
            std::cout << "  {\n"
            << "    timeO2Start : " << run.timeO2Start.to_string() << '\n'
            << "    runType : " << run.runType << '\n'
            << "    nFlps : " << run.nFlps << '\n'
            << "    bytesReadOut : " << run.bytesReadOut << '\n'
            << "  },\n"; 
        }
    }

    return 0;
}
