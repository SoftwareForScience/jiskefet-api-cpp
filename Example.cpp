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
}

/*namespace
{
    struct GetRunParameters
    {
        boost::optional<utility::string_t> orderBy;
        boost::optional<utility::string_t> orderDirection;
        boost::optional<utility::string_t> pageSize;
        boost::optional<utility::string_t> pageNumber;
        boost::optional<utility::string_t> runNumber;
        boost::optional<utility::datetime> startTimeO2Start;
        boost::optional<utility::datetime> endTimeO2Start;
        boost::optional<utility::datetime> startTimeTrgStart;
        boost::optional<utility::datetime> endTimeTrgStart;
        boost::optional<utility::datetime> startTimeTrgEnd;
        boost::optional<utility::datetime> endTimeTrgEnd;
        boost::optional<utility::datetime> startTimeO2End;
        boost::optional<utility::datetime> endTimeO2End;
        boost::optional<utility::string_t> activityId;
        boost::optional<int32_t> runType;
        boost::optional<int32_t> runQuality;
    };

    class JiskefetApi 
    {
        public:
        JiskefetApi(std::string hostUrl, std::string apiPath, std::string apiToken) 
        {
            apiClient = std::make_shared<io::swagger::client::api::ApiClient>();
            apiConfig = std::make_shared<io::swagger::client::api::ApiConfiguration>();
            std::string baseUrl = "http://" + hostUrl + "/" + apiPath;
            apiConfig->setBaseUrl(baseUrl);
            apiConfig->setApiKey("Bearer", apiToken);
            apiClient->setConfiguration(apiConfig);
        }

        void PostRun() 
        {
            io::swagger::client::api::RunsApi runsApi(apiClient);

            web::json::value val = web::json::value::object();

            using namespace io::swagger::client::api;
            val[utility::conversions::to_string_t("timeO2Start")] = ModelBase::toJson(m_TimeO2Start);
            val[utility::conversions::to_string_t("timeTrgStart")] = ModelBase::toJson(m_TimeTrgStart);
            val[utility::conversions::to_string_t("timeO2End")] = ModelBase::toJson(m_TimeO2End);
            val[utility::conversions::to_string_t("timeTrgEnd")] = ModelBase::toJson(m_TimeTrgEnd);
            val[utility::conversions::to_string_t("runType")] = ModelBase::toJson(m_RunType);
            val[utility::conversions::to_string_t("runQuality")] = ModelBase::toJson(m_RunQuality);
            val[utility::conversions::to_string_t("activityId")] = ModelBase::toJson(m_ActivityId);
            val[utility::conversions::to_string_t("nDetectors")] = ModelBase::toJson(m_NDetectors);
            val[utility::conversions::to_string_t("nFlps")] = ModelBase::toJson(m_NFlps);
            val[utility::conversions::to_string_t("nEpns")] = ModelBase::toJson(m_NEpns);
            val[utility::conversions::to_string_t("nTimeframes")] = ModelBase::toJson(m_NTimeframes);
            val[utility::conversions::to_string_t("nSubtimeframes")] = ModelBase::toJson(m_NSubtimeframes);
            val[utility::conversions::to_string_t("bytesReadOut")] = ModelBase::toJson(m_BytesReadOut);
            val[utility::conversions::to_string_t("bytesTimeframeBuilder")] = ModelBase::toJson(m_BytesTimeframeBuilder);

            auto createRunDto = std::make_shared<io::swagger::client::api::CreateRunDto>();
            pplx::task<void> task = runsApi.runsPost(createRunDto);
        }

        private:
        std::shared_ptr<io::swagger::client::api::ApiClient> apiClient;
        std::shared_ptr<io::swagger::client::api::ApiConfiguration> apiConfig;
    };
}*/


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
        << "JISKEFET_API_TOKEN: " << apiToken << std::endl;

    crossplat::threadpool::initialize_with_threads(1);
    auto apiClient = std::make_shared<ApiClient>();
    auto apiConfig = std::make_shared<ApiConfiguration>();
    apiConfig->setBaseUrl(baseUrl);
    apiConfig->setApiKey("Authorization", " Bearer " + apiToken);
    apiConfig->setUserAgent("JiskefetCppApi");
    apiClient->setConfiguration(apiConfig);
    RunsApi runsApi(apiClient);

    
    web::json::value val = web::json::value::object();
    val["timeO2Start"] = ModelBase::toJson(utility::datetime().from_string("2018-11-26T16:43:22.279Z"));
    val["timeTrgStart"] = ModelBase::toJson(utility::datetime().from_string("2018-11-26T16:43:22.279Z"));
    val["timeO2End"] = ModelBase::toJson(utility::datetime().from_string("2018-11-26T16:43:22.279Z"));
    val["timeTrgEnd"] = ModelBase::toJson(utility::datetime().from_string("2018-11-26T16:43:22.279Z"));
    val["runType"] = ModelBase::toJson(utility::string_t("my-run-type"));
    val["runQuality"] = ModelBase::toJson(utility::string_t("my-run-quality"));
    val["activityId"] = ModelBase::toJson(utility::string_t("my-activity-id"));
    val["nDetectors"] = ModelBase::toJson(int32_t(123));
    val["nFlps"] = ModelBase::toJson(int32_t(200));
    val["nEpns"] = ModelBase::toJson(int32_t(1000));
    val["nTimeframes"] = ModelBase::toJson(int32_t(12312));
    val["nSubtimeframes"] = ModelBase::toJson(int32_t(1231231));
    val["bytesReadOut"] = ModelBase::toJson(int32_t(6899397343));
    val["bytesTimeframeBuilder"] = ModelBase::toJson(int32_t(1235435));
    auto createRunDto = std::make_shared<model::CreateRunDto>();
    std::cout << "PTR=" << ((void*) createRunDto.get()) << std::endl;
    createRunDto->fromJson(val);
    pplx::task<void> taskRunsPost = runsApi.runsPost(createRunDto);
    taskRunsPost.get();

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
    
    try {
        // taskRunsGet.get();
        std::cout << "Executing HTTP request..." << std::fflush;
        std::shared_ptr<Object> result = taskRunsGet.get();
        std::cout << " done!" << std::endl;
        std::cout << "Result:\n" << result << std::endl;
    } catch(const std::exception& e) {
        std::cout << "runsGet() exception: " << e.what() << '\n';
    }

    return 0;
}
