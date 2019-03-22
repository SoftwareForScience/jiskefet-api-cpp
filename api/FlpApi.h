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
 * FlpApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_FlpApi_H_
#define IO_SWAGGER_CLIENT_API_FlpApi_H_


#include "../ApiClient.h"

#include "CreateFlpDto.h"
#include "Object.h"
#include "PatchFlpDto.h"
#include <cpprest/details/basic_types.h>

#include <boost/optional.hpp>

namespace io {
namespace swagger {
namespace client {
namespace api {

using namespace io::swagger::client::model;

class  FlpApi
{
public:
    FlpApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~FlpApi();
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="name"></param>
    /// <param name="id"></param>
    pplx::task<std::shared_ptr<Object>> flpNameRunsIdGet(
        utility::string_t name,
        int64_t id
    );
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="patchFlpDto"></param>
    /// <param name="name"></param>
    /// <param name="id"></param>
    pplx::task<std::shared_ptr<Object>> flpNameRunsIdPatch(
        std::shared_ptr<PatchFlpDto> patchFlpDto,
        utility::string_t name,
        int64_t id
    );
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="createFlpDto"></param>
    pplx::task<std::shared_ptr<Object>> flpPost(
        std::shared_ptr<CreateFlpDto> createFlpDto
    );

protected:
    std::shared_ptr<ApiClient> m_ApiClient;
};

}
}
}
}

#endif /* IO_SWAGGER_CLIENT_API_FlpApi_H_ */
