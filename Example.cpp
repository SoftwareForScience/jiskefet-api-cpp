#include <string>
#include <iostream>
#include "ApiClient.h"
#include "api/RunsApi.h"
#include "boost/none.hpp"
#include "cpprest/oauth2.h"

namespace 
{
    std::string getEnvString(const std::string& key)
    {
        char* env = std::getenv(key.c_str());
        return (env == nullptr) ? std::string("") : std::string(env);
    }
}


int main(int argc, char const *argv[])
{
    std::cout << "Hello jiskefet-api-cpp!" << std::endl;

	std::string hostUrl = getEnvString("JISKEFET_HOST");
	std::string apiPath = getEnvString("JISKEFET_PATH");
    std::string apiToken = getEnvString("JISKEFET_API_TOKEN");
    std::string baseUrl = "http://" + hostUrl + "/" + apiPath;

    std::cout << "JISKEFET_HOST:      " << hostUrl << '\n'
        << "JISKEFET_API_PATH:  " << apiPath << '\n'
        << "JISKEFET_API_TOKEN: " << apiToken << '\n';

// fmt.Printf("JISKEFET_HOST:      %s\n", hostUrl)
// fmt.Printf("JISKEFET_API_PATH:  %s\n", apiPath)
// fmt.Printf("JISKEFET_API_TOKEN: %s\n", apiToken)

    using namespace io;
    using namespace swagger;
    using namespace client;
    using namespace api;

    std::shared_ptr<ApiClient> apiClient(new ApiClient);
    std::shared_ptr<ApiConfiguration> apiConfig(new ApiConfiguration);
    apiConfig->setBaseUrl(baseUrl);
    apiConfig->setApiKey("Bearer", apiToken);
    //web::http::client::http_client_config httpConfig;
    //web::http::oauth2::experimental::oauth2_config oauth2Config;
    //oauth2Config.set_bearer_auth(true);
    //oauth2Config.set_access_token_key(accessToken);
    //httpConfig.set_oauth2(oauth2Config);
    //apiConfig->setHttpConfig(httpConfig);
    apiClient->setConfiguration(apiConfig);
    RunsApi runsApi(apiClient);

    pplx::task<std::shared_ptr<Object>> task = runsApi.runsGet(
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

    std::cout << task.get() << '\n';

    // task.then([=](pplx::task<std::shared_ptr<Object>> example) {
    //     try {
    //         std::cout << example.get() << '\n';
    //     } catch(const std::exception& e) {
    //         std::cout << "getExample() exception: " << e.what() << '\n';
    //     }
    // });    

    return 0;
}
