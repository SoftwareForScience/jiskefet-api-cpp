#pragma once

#include <string>
#include "JiskefetInterface.h"
#include "ApiClient.h"
#include "ApiConfiguration.h"

namespace jiskefet
{

class JiskefetApi : public virtual JiskefetInterface
{
    public:
    JiskefetApi(std::string url, std::string token);
    virtual void createRun(const CreateRunParameters& parameters) override;
    virtual std::vector<Run> getRuns(const GetRunsParameters& parameters) override;
    virtual void createLog(const CreateLogParameters& parameters) override;
    virtual std::vector<Log> getLogs(const GetLogsParameters& parameters) override;
    
    private:
    std::shared_ptr<io::swagger::client::api::ApiClient> apiClient;
};

}