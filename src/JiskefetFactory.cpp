#include "JiskefetFactory.h"
#include "JiskefetApi.h"

namespace jiskefet
{
std::unique_ptr<JiskefetInterface> getApiInstance(std::string url, std::string token)
{
    return std::make_unique<JiskefetApi>(url, token);
}
}