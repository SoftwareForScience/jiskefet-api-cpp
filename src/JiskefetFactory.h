#pragma once

#include "JiskefetInterface.h"
#include <memory>

namespace jiskefet
{
std::unique_ptr<JiskefetInterface> getApiInstance(std::string url, std::string token);
}