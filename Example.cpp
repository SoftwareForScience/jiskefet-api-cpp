#include <string>
#include <iostream>
#include "ApiClient.h"
#include "api/RunsApi.h"
#include "boost/none.hpp"
#include "cpprest/oauth2.h"
#include "pplx/threadpool.h"
#include "jiskefet/JiskefetFactory.h"

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
    jiskefet::PostRunArguments postRunArguments;
    postRunArguments.timeO2Start = utility::datetime().from_string("2018-11-26T16:43:22.279Z");
    postRunArguments.timeO2Start = utility::datetime().from_string("2018-11-26T16:43:22.279Z");
    postRunArguments.timeTrgStart = utility::datetime().from_string("2018-11-26T16:43:22.279Z");
    postRunArguments.timeO2End = utility::datetime().from_string("2018-11-26T16:43:22.279Z");
    postRunArguments.timeTrgEnd = utility::datetime().from_string("2018-11-26T16:43:22.279Z");
    postRunArguments.runType = "my-run-type";
    postRunArguments.runQuality = "my-run-quality";
    postRunArguments.activityId = "cpp-api";
    postRunArguments.nDetectors = 123;
    postRunArguments.nFlps = 200;
    postRunArguments.nEpns = 1000;
    postRunArguments.nTimeframes = 12312;
    postRunArguments.nSubtimeframes = 12312312;
    postRunArguments.bytesReadOut = 1024*1024*1024;
    postRunArguments.bytesTimeframeBuilder = 512*1024*1024;
    api->postRun(postRunArguments);

    // Get run
    jiskefet::GetRunsArguments getRunsArguments;
    getRunsArguments.pageSize = "25";
    std::vector<jiskefet::Run> runs = api->getRuns(getRunsArguments);
    for (const auto& run : runs) {
        std::cout << "  {\n"
        << "    timeO2Start : " << run.timeO2Start.to_string() << '\n'
        << "    runType : " << run.runType << '\n'
        << "    nFlps : " << run.nFlps << '\n'
        << "    bytesReadOut : " << run.bytesReadOut << '\n'
        << "  },\n";
    }

    return 0;
}