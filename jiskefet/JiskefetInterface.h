#pragma once
#include <vector>
#include "CreateLogParameters.h"
#include "CreateRunParameters.h"
#include "GetLogsParameters.h"
#include "GetRunsParameters.h"
#include "Log.h"
#include "LogOrigin.h"
#include "LogSubtype.h"
#include "OrderDirection.h"
#include "Run.h"


namespace jiskefet
{
class JiskefetInterface {
    public: 
    virtual void createRun(const CreateRunParameters& parameters) = 0;
    virtual std::vector<Run> getRuns(const GetRunsParameters& parameters) = 0;
    virtual void createLog(const CreateLogParameters& parameters) = 0;
    virtual std::vector<Log> getLogs(const GetLogsParameters& parameters) = 0;
};
}