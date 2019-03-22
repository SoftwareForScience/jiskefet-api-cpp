/**
 * Jiskefet
 * Running with /api base path
 *
 * OpenAPI spec version: 0.1.0
 * 
 *
 * NOTE: This class is auto generated by the swagger code generator 2.4.2.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 */

/*
 * LogsApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_LogsApi_H_
#define IO_SWAGGER_CLIENT_API_LogsApi_H_


#include "../ApiClient.h"

#include "CreateLogDto.h"
#include "LinkRunToLogDto.h"
#include "Object.h"
#include <cpprest/details/basic_types.h>

#include <boost/optional.hpp>

namespace io {
namespace swagger {
namespace client {
namespace api {

using namespace io::swagger::client::model;

class  LogsApi
{
public:
    LogsApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~LogsApi();
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="orderBy">On which field to order on. (optional)</param>
    /// <param name="orderDirection">The order direction, either ascending or descending. (optional)</param>
    /// <param name="pageSize">The maximum amount of logs in each result. (optional, default to 25)</param>
    /// <param name="pageNumber">The current page, i.e. the offset in the result set based on pageSize. (optional, default to 1)</param>
    /// <param name="logId">The id of the log. (optional)</param>
    /// <param name="searchterm">Search for a term that exists in the title field of a log. (optional)</param>
    /// <param name="subtype">The subtype of the log. (optional)</param>
    /// <param name="origin">The origin/creator of the log. (optional)</param>
    /// <param name="startCreationTime">The lower bound of the creation time filter range. (optional)</param>
    /// <param name="endCreationTime">The upper bound of the creation time filter range. (optional)</param>
    /// <param name="user">The author of the log.. (optional)</param>
    pplx::task<std::shared_ptr<Object>> logsGet(
        boost::optional<utility::string_t> orderBy,
        boost::optional<utility::string_t> orderDirection,
        boost::optional<utility::string_t> pageSize,
        boost::optional<utility::string_t> pageNumber,
        boost::optional<utility::string_t> logId,
        boost::optional<utility::string_t> searchterm,
        boost::optional<utility::string_t> subtype,
        boost::optional<utility::string_t> origin,
        boost::optional<utility::string_t> startCreationTime,
        boost::optional<utility::string_t> endCreationTime,
        boost::optional<utility::string_t> user
    );
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="id"></param>
    pplx::task<std::shared_ptr<Object>> logsIdGet(
        double id
    );
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="linkRunToLogDto"></param>
    /// <param name="id"></param>
    pplx::task<std::shared_ptr<Object>> logsIdRunsPatch(
        std::shared_ptr<LinkRunToLogDto> linkRunToLogDto,
        double id
    );
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="createLogDto"></param>
    pplx::task<std::shared_ptr<Object>> logsPost(
        std::shared_ptr<CreateLogDto> createLogDto
    );

protected:
    std::shared_ptr<ApiClient> m_ApiClient;
};

}
}
}
}

#endif /* IO_SWAGGER_CLIENT_API_LogsApi_H_ */

