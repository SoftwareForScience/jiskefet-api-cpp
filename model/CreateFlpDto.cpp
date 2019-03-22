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



#include "CreateFlpDto.h"

namespace io {
namespace swagger {
namespace client {
namespace model {

CreateFlpDto::CreateFlpDto()
{
    m_FlpName = utility::conversions::to_string_t("");
    m_FlpHostname = utility::conversions::to_string_t("");
    m_Run = 0.0;
}

CreateFlpDto::~CreateFlpDto()
{
}

void CreateFlpDto::validate()
{
    // TODO: implement validation
}

web::json::value CreateFlpDto::toJson() const
{
    web::json::value val = web::json::value::object();

    val[utility::conversions::to_string_t("flpName")] = ModelBase::toJson(m_FlpName);
    val[utility::conversions::to_string_t("flpHostname")] = ModelBase::toJson(m_FlpHostname);
    val[utility::conversions::to_string_t("run")] = ModelBase::toJson(m_Run);

    return val;
}

void CreateFlpDto::fromJson(web::json::value& val)
{
    setFlpName(ModelBase::stringFromJson(val[utility::conversions::to_string_t("flpName")]));
    setFlpHostname(ModelBase::stringFromJson(val[utility::conversions::to_string_t("flpHostname")]));
    setRun(ModelBase::doubleFromJson(val[utility::conversions::to_string_t("run")]));
}

void CreateFlpDto::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t("."))
    {
        namePrefix += utility::conversions::to_string_t(".");
    }

    multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("flpName"), m_FlpName));
    multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("flpHostname"), m_FlpHostname));
    multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("run"), m_Run));
}

void CreateFlpDto::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t("."))
    {
        namePrefix += utility::conversions::to_string_t(".");
    }

    setFlpName(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("flpName"))));
    setFlpHostname(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("flpHostname"))));
    setRun(ModelBase::doubleFromHttpContent(multipart->getContent(utility::conversions::to_string_t("run"))));
}

utility::string_t CreateFlpDto::getFlpName() const
{
    return m_FlpName;
}


void CreateFlpDto::setFlpName(utility::string_t value)
{
    m_FlpName = value;
    
}
utility::string_t CreateFlpDto::getFlpHostname() const
{
    return m_FlpHostname;
}


void CreateFlpDto::setFlpHostname(utility::string_t value)
{
    m_FlpHostname = value;
    
}
double CreateFlpDto::getRun() const
{
    return m_Run;
}


void CreateFlpDto::setRun(double value)
{
    m_Run = value;
    
}
}
}
}
}

