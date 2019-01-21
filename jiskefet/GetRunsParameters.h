#pragma once
#include <cstdint>
#include <string>
#include <boost/optional.hpp>
#include <boost/date_time/posix_time/ptime.hpp>


namespace jiskefet
{
struct GetRunsParameters
{
    boost::optional<std::string> orderBy;
    boost::optional<OrderDirection> orderDirection;
    boost::optional<int64_t> pageSize;
    boost::optional<int64_t> pageNumber;
    boost::optional<int64_t> runNumber;
    boost::optional<boost::posix_time::ptime> startTimeO2Start;
    boost::optional<boost::posix_time::ptime> endTimeO2Start;
    boost::optional<boost::posix_time::ptime> startTimeTrgStart;
    boost::optional<boost::posix_time::ptime> endTimeTrgStart;
    boost::optional<boost::posix_time::ptime> startTimeTrgEnd;
    boost::optional<boost::posix_time::ptime> endTimeTrgEnd;
    boost::optional<boost::posix_time::ptime> startTimeO2End;
    boost::optional<boost::posix_time::ptime> endTimeO2End;
    boost::optional<std::string> activityId;
    boost::optional<int32_t> runType;
    boost::optional<int32_t> runQuality;
};
}