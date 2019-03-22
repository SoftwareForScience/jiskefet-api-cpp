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
 * SubsystemsApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_SubsystemsApi_H_
#define IO_SWAGGER_CLIENT_API_SubsystemsApi_H_


#include "../ApiClient.h"

#include "Object.h"

#include <boost/optional.hpp>

namespace io {
namespace swagger {
namespace client {
namespace api {

using namespace io::swagger::client::model;

class  SubsystemsApi
{
public:
    SubsystemsApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~SubsystemsApi();
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    pplx::task<void> subsystemsGet(
    );
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="id"></param>
    pplx::task<std::shared_ptr<Object>> subsystemsIdGet(
        int64_t id
    );

protected:
    std::shared_ptr<ApiClient> m_ApiClient;
};

}
}
}
}

#endif /* IO_SWAGGER_CLIENT_API_SubsystemsApi_H_ */

