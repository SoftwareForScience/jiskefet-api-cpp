/**
 * Jiskefet
 * Running with /api base path
 *
 * OpenAPI spec version: 0.1.0
 * 
 *
 * NOTE: This class is auto generated by the swagger code generator 2.4.4.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 */

/*
 * PatchFlpDto.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_MODEL_PatchFlpDto_H_
#define IO_SWAGGER_CLIENT_MODEL_PatchFlpDto_H_


#include "../ModelBase.h"


namespace io {
namespace swagger {
namespace client {
namespace model {

/// <summary>
/// 
/// </summary>
class  PatchFlpDto
    : public ModelBase
{
public:
    PatchFlpDto();
    virtual ~PatchFlpDto();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    void fromJson(web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    void fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// PatchFlpDto members

    /// <summary>
    /// Number of subtimeframes processed in this FLP. Updated regularly.
    /// </summary>
    int64_t getNSubTimeframes() const;
        void setNSubTimeframes(int64_t value);
    /// <summary>
    /// data volume out from the readout &#39;equipment&#39; component in bytes. Can reach PetaBytes.Updated regularly.
    /// </summary>
    int64_t getEquipmentBytes() const;
        void setEquipmentBytes(int64_t value);
    /// <summary>
    /// data volume out from the readout &#39;recording&#39; component in bytes. Can reach PetaBytes. Updated regularly.
    /// </summary>
    int64_t getRecordingBytes() const;
        void setRecordingBytes(int64_t value);
    /// <summary>
    /// data volume out from the readout &#39;fmq&#39; component in bytes. Can reach PetaBytes. Updated regularly.
    /// </summary>
    int64_t getFairMQBytes() const;
        void setFairMQBytes(int64_t value);

protected:
    int64_t m_NSubTimeframes;
        int64_t m_EquipmentBytes;
        int64_t m_RecordingBytes;
        int64_t m_FairMQBytes;
    };

}
}
}
}

#endif /* IO_SWAGGER_CLIENT_MODEL_PatchFlpDto_H_ */
