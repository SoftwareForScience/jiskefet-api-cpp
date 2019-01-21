#pragma once
#include <vector>
#include <cstdint>
#include <cpprest/asyncrt_utils.h>
#include "LogSubtype.h"
#include "LogOrigin.h"

namespace jiskefet
{
struct CreateLogParameters
{
    struct Attachment
    {
        std::string title;
        std::string fileMime;
        std::string fileData;
    };

    LogSubtype subtype;
    LogOrigin origin;
    std::string title;
    std::string text;
    std::vector<Attachment> attachments;
    std::vector<int64_t> runIds;
};
}