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
 * Log.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_MODEL_Log_H_
#define IO_SWAGGER_CLIENT_MODEL_Log_H_


#include "../ModelBase.h"

#include <cpprest/details/basic_types.h>
#include <vector>

namespace io {
namespace swagger {
namespace client {
namespace model {

/// <summary>
/// 
/// </summary>
class  Log
    : public ModelBase
{
public:
    Log();
    virtual ~Log();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    void fromJson(web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    void fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Log members

    /// <summary>
    /// 
    /// </summary>
    int64_t getLogId() const;
        void setLogId(int64_t value);
    /// <summary>
    /// 
    /// </summary>
    utility::string_t getOrigin() const;
        void setOrigin(utility::string_t value);
    /// <summary>
    /// 
    /// </summary>
    utility::datetime getCreationTime() const;
        void setCreationTime(utility::datetime value);
    /// <summary>
    /// 
    /// </summary>
    utility::string_t getTitle() const;
        void setTitle(utility::string_t value);
    /// <summary>
    /// 
    /// </summary>
    utility::string_t getBody() const;
        void setBody(utility::string_t value);
    /// <summary>
    /// 
    /// </summary>
    int64_t getSubsystemFkSubsystemId() const;
    bool subsystemFkSubsystemIdIsSet() const;
    void unsetSubsystemFkSubsystemId();
    void setSubsystemFkSubsystemId(int64_t value);
    /// <summary>
    /// 
    /// </summary>
    utility::datetime getAnnouncementValidUntil() const;
    bool announcementValidUntilIsSet() const;
    void unsetAnnouncementValidUntil();
    void setAnnouncementValidUntil(utility::datetime value);
    /// <summary>
    /// 
    /// </summary>
    int64_t getCommentFkParentLogId() const;
    bool commentFkParentLogIdIsSet() const;
    void unsetCommentFkParentLogId();
    void setCommentFkParentLogId(int64_t value);
    /// <summary>
    /// 
    /// </summary>
    int64_t getCommentFkRootLogId() const;
    bool commentFkRootLogIdIsSet() const;
    void unsetCommentFkRootLogId();
    void setCommentFkRootLogId(int64_t value);
    /// <summary>
    /// 
    /// </summary>
    std::vector<utility::string_t>& getRuns();
        void setRuns(std::vector<utility::string_t> value);

protected:
    int64_t m_LogId;
        utility::string_t m_Origin;
        utility::datetime m_CreationTime;
        utility::string_t m_Title;
        utility::string_t m_Body;
        int64_t m_SubsystemFkSubsystemId;
    bool m_SubsystemFkSubsystemIdIsSet;
    utility::datetime m_AnnouncementValidUntil;
    bool m_AnnouncementValidUntilIsSet;
    int64_t m_CommentFkParentLogId;
    bool m_CommentFkParentLogIdIsSet;
    int64_t m_CommentFkRootLogId;
    bool m_CommentFkRootLogIdIsSet;
    std::vector<utility::string_t> m_Runs;
    };

}
}
}
}

#endif /* IO_SWAGGER_CLIENT_MODEL_Log_H_ */