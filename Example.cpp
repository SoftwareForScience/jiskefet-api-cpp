#include <string>
#include <iostream>
#include "ApiClient.h"
#include "api/RunsApi.h"
#include "cpprest/oauth2.h"
#include "jiskefet/JiskefetFactory.h"

#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


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
	std::string url = getEnvString("JISKEFET_URL");
    std::string apiToken = getEnvString("JISKEFET_API_TOKEN");
    std::cout << "JISKEFET_URL: " << url << '\n'
        << "JISKEFET_API_TOKEN: " << apiToken << '\n';

    auto api = jiskefet::getApiInstance(url, apiToken);

    // Post run
    {
        auto now = boost::posix_time::microsec_clock::universal_time();
        auto sometime = boost::posix_time::from_iso_extended_string("2007-03-01T13:00:00");

        jiskefet::CreateRunParameters params;
        params.timeO2Start = sometime;
        params.timeTrgStart = sometime;
        params.timeO2End = now;
        params.timeTrgEnd = now;
        params.runType = "my-run-type";
        params.runQuality = "my-run-quality";
        params.activityId = "cpp-api";
        params.nDetectors = 123;
        params.nFlps = 200;
        params.nEpns = 1000;
        params.nTimeframes = 1231;
        params.nSubtimeframes = 12312;
        params.bytesReadOut = 1024*1024;
        params.bytesTimeframeBuilder = 512*1024;
        api->createRun(params);
    }

    // Get run
    {
        jiskefet::GetRunsParameters params;
        params.pageSize = 3;
        params.orderDirection = jiskefet::OrderDirection::DESC;
        std::vector<jiskefet::Run> runs = api->getRuns(params);
        for (const auto& run : runs) {
            std::cout << "  {\n"
            << "    timeO2Start : " << boost::posix_time::to_iso_extended_string(run.timeO2Start) << '\n'
            << "    runType : " << run.runType << '\n'
            << "    nFlps : " << run.nFlps << '\n'
            << "    bytesReadOut : " << run.bytesReadOut << '\n'
            << "  },\n";
        }
    }

    return 0;
}