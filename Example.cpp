#include <string>
#include <iostream>
#include <thread>
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

    // Start & end run, with FLPs
    {
        const int64_t runNumber = rand()*1000.0;
        auto now = boost::posix_time::microsec_clock::universal_time();
        api->runStart(runNumber, now, now, "cpp-api", RunType::TECHNICAL, 123, 200, 100);
        api->flpAdd(runNumber, "flp-1", "localhost");
        api->flpAdd(runNumber, "flp-2", "localhost");
        std::this_thread::sleep_for(std::chrono::seconds(1));

        api->flpUpdateCounters(runNumber, "flp-1", 123, 123408, 5834, 9192);
        api->flpUpdateCounters(runNumber, "flp-2", 13, 318, 23, 952);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        api->flpUpdateCounters(runNumber, "flp-1", 234, 323408, 6834, 9292);
        
        now = boost::posix_time::microsec_clock::universal_time();
        api->runEnd(runNumber, now, now, RunQuality::UNKNOWN);
    }

    // Get run
    {
        jiskefet::GetRunsParameters params;
        params.pageSize = 3;
        params.orderDirection = jiskefet::OrderDirection::DESC;
        std::vector<jiskefet::Run> runs = api->getRuns(params);
        for (const auto& run : runs) {
            std::cout << "  {\n"
            << "    runNumber : " << run.runNumber << '\n'
            << "    timeO2Start : " << boost::posix_time::to_iso_extended_string(run.timeO2Start) << '\n'
            << "    runType : " << run.runType << '\n'
            << "    nFlps : " << run.nFlps << '\n'
            << "    bytesReadOut : " << run.bytesReadOut << '\n'
            << "  },\n";
        }
    }

    return 0;
}