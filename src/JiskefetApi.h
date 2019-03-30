#pragma once

#include <string>
#include "JiskefetInterface.h"
#include "cpprest-client/ApiClient.h"
#include "cpprest-client/ApiConfiguration.h"

namespace jiskefet
{

class JiskefetApi : public virtual JiskefetInterface
{
    public:
    JiskefetApi(std::string url, std::string token);
    virtual void runStart(int64_t runNumber, boost::posix_time::ptime o2Start,
      boost::posix_time::ptime triggerStart, std::string activityId, 
      RunType runType, int64_t nDetectors, int64_t nFlps, int64_t nEpns) override;
    virtual void runEnd(int64_t runNumber, boost::posix_time::ptime o2End, boost::posix_time::ptime triggerEnd,
      RunQuality runQuality) override;
    virtual void flpAdd(int64_t runNumber, std::string flpName, std::string hostName) override;
    virtual void flpUpdateCounters(int64_t runNumber, std::string flpName, int64_t nSubtimeframes, int64_t nEquipmentBytes,
      int64_t nRecordingBytes, int64_t nFairMqBytes) override;
    virtual std::vector<Run> getRuns(const GetRunsParameters& parameters) override;
    virtual int64_t createLog(const CreateLogParameters& parameters) override;
    virtual std::vector<Log> getLogs(const GetLogsParameters& parameters) override;
    
    private:
    std::shared_ptr<io::swagger::client::api::ApiClient> apiClient;
};

}