cmake_minimum_required(VERSION 3.5.2 FATAL_ERROR)

project(
    JiskefetApiCpp
    VERSION 0.3.3
    LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# BUILD TYPE
message("A ${CMAKE_BUILD_TYPE} build configuration is detected")

# Update require components as necessary
find_package(Boost 1.45.0 REQUIRED COMPONENTS thread system regex date_time program_options filesystem)
find_package(OpenSSL 1.0.0 REQUIRED)
find_library(CPPREST_LIBRARIES cpprest PATHS ${CPPREST_LIB} PATH_SUFFIXES lib lib64)

# build and set path to cpp rest sdk
set(CPPREST_INCLUDE_DIR ${CPPREST_ROOT}/include)

if( NOT DEFINED CPPREST_ROOT )
    message( FATAL_ERROR "Failed to find cpprest SDK (or missing components). Double check that \"CPPREST_ROOT\" is properly set")
endif( NOT DEFINED CPPREST_ROOT )

set(SOURCE_FILES
    src/cpprest-client/ApiClient.cpp
    src/cpprest-client/ApiConfiguration.cpp
    src/cpprest-client/ApiException.cpp
    src/cpprest-client/HttpContent.cpp
    src/cpprest-client/JsonBody.cpp
    src/cpprest-client/ModelBase.cpp
    src/cpprest-client/MultipartFormData.cpp
    src/cpprest-client/Object.cpp
    src/cpprest-client/api/AttachmentsApi.cpp
    src/cpprest-client/api/AuthenticationApi.cpp
    src/cpprest-client/api/FlpApi.cpp
    src/cpprest-client/api/LogsApi.cpp
    src/cpprest-client/api/OverviewApi.cpp
    src/cpprest-client/api/RunsApi.cpp
    src/cpprest-client/api/SettingApi.cpp
    src/cpprest-client/api/SubsystemsApi.cpp
    src/cpprest-client/api/UsersApi.cpp
    src/cpprest-client/model/CreateAttachmentDto.cpp
    src/cpprest-client/model/CreateFlpDto.cpp
    src/cpprest-client/model/CreateLogDto.cpp
    src/cpprest-client/model/CreateRunDto.cpp
    src/cpprest-client/model/CreateSubSystemPermissionDto.cpp
    src/cpprest-client/model/FlpRole.cpp
    src/cpprest-client/model/LinkLogToRunDto.cpp
    src/cpprest-client/model/LinkRunToLogDto.cpp
    src/cpprest-client/model/Log.cpp
    src/cpprest-client/model/PatchFlpDto.cpp
    src/cpprest-client/model/PatchRunDto.cpp
    src/cpprest-client/model/Run.cpp
    src/cpprest-client/model/SubSystem.cpp
    src/cpprest-client/model/User.cpp
    src/JiskefetApi.cpp
    src/JiskefetFactory.cpp)

add_library(
    ${PROJECT_NAME}
    ${SOURCE_FILES})

target_include_directories(
    JiskefetApiCpp
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/cpprest-client>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/cpprest-client/api>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/cpprest-client/model>
    PRIVATE
    ${CPPREST_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR})

target_link_libraries(
    JiskefetApiCpp
    PRIVATE
    ${CPPREST_LIBRARIES} 
    ${Boost_LIBRARIES} 
    ${OPENSSL_LIBRARIES} 
    pthread)

target_compile_features(
    ${PROJECT_NAME}
    PUBLIC
    cxx_std_17)

add_executable(
    jiskefet-api-cpp-example
    src/Example.cpp)

target_link_libraries(
    jiskefet-api-cpp-example 
    PRIVATE
    ${PROJECT_NAME})


# Set CMAKE_INSTALL_LIBDIR explicitly to lib (to avoid lib64 on CC7)
set(CMAKE_INSTALL_LIBDIR lib)

install(
    TARGETS jiskefet-api-cpp-example JiskefetApiCpp
    EXPORT JiskefetApiCppTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
    EXPORT JiskefetApiCppTargets
    FILE JiskefetApiCppTargets.cmake
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/JiskefetApiCpp")

install(
    DIRECTORY src/
    DESTINATION include/JiskefetApiCpp
    FILES_MATCHING PATTERN "*.h")

# Configure and install package config files
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/JiskefetApiCppConfigVersion.cmake"
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
    cmake/JiskefetApiCppConfig.cmake.in 
    cmake/JiskefetApiCppConfig.cmake
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/JiskefetApiCpp"
    PATH_VARS CMAKE_INSTALL_PREFIX)

install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/JiskefetApiCppConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/JiskefetApiCppConfigVersion.cmake"
    DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/JiskefetApiCpp)
