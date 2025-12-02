cmake_minimum_required(VERSION 3.14)
project(cpp_core VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set policy version minimum for dependencies
set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "Minimum CMake policy version for subprojects")

# Set policies for compatibility with dependencies
if(POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()

# ============================================
# Compilation Flags
# ============================================

# Common flags for all configurations
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter  # Allow unused parameters (for interfaces)
)

# Debug flags
# Note: -Werror removed to allow dependencies (Oat++) to compile with warnings
# Strict warnings are applied only to our code via target_compile_options
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

# Release flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# RelWithDebInfo flags
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g -DNDEBUG")

# ============================================
# Dependencies via FetchContent
# ============================================

# Disable tests for all dependencies to avoid conflicts
set(BUILD_TESTING OFF CACHE BOOL "Build tests" FORCE)
set(OATPP_BUILD_TESTS OFF CACHE BOOL "Build Oat++ tests" FORCE)
set(OATPP_SWAGGER_BUILD_TESTS OFF CACHE BOOL "Build Oat++ Swagger tests" FORCE)
set(OATPP_POSTGRESQL_BUILD_TESTS OFF CACHE BOOL "Build Oat++ PostgreSQL tests" FORCE)

# Always use FetchContent for oatpp to ensure correct architecture and get oatpp-test
include(FetchContent)

# Oat++ (main framework) - using 1.3.0 (latest stable)
FetchContent_Declare(
    oatpp
    GIT_REPOSITORY https://github.com/oatpp/oatpp.git
    GIT_TAG 1.3.0
)
FetchContent_MakeAvailable(oatpp)
message(STATUS "Using oatpp from FetchContent")
set(OATPP_TEST_LIB oatpp-test)

# Oat++ Swagger (for API documentation)
# Configure oatpp-swagger to use CUSTOM location mode to work with FetchContent
FetchContent_Declare(
    oatpp-swagger
    GIT_REPOSITORY https://github.com/oatpp/oatpp-swagger.git
    GIT_TAG 1.3.0
)

# Set oatpp-swagger to use CUSTOM mode AFTER Declare but BEFORE MakeAvailable
# Use CACHE FORCE to ensure variables are available to subprojects
set(OATPP_MODULES_LOCATION "CUSTOM" CACHE STRING "Location where to find oatpp modules" FORCE)
set(OATPP_DIR_SRC "${oatpp_SOURCE_DIR}/src" CACHE PATH "Path to oatpp module directory (sources)" FORCE)
set(OATPP_DIR_LIB "${oatpp_BINARY_DIR}/src" CACHE PATH "Path to directory with liboatpp" FORCE)

FetchContent_MakeAvailable(oatpp-swagger)

# Define OATPP_SWAGGER_RES_PATH for Swagger resources
set(OATPP_SWAGGER_RES_PATH "${CMAKE_BINARY_DIR}/_deps/oatpp-swagger-src/res")

# Oat++ PostgreSQL - using 1.3.0 for compatibility with oatpp 1.3.0
FetchContent_Declare(
    oatpp-postgresql
    GIT_REPOSITORY https://github.com/oatpp/oatpp-postgresql.git
    GIT_TAG 1.3.0
)

# Set CUSTOM mode AFTER Declare but BEFORE MakeAvailable
# Use CACHE FORCE to ensure variables are available to subprojects
set(OATPP_MODULES_LOCATION "CUSTOM" CACHE STRING "Location where to find oatpp modules" FORCE)
set(OATPP_DIR_SRC "${oatpp_SOURCE_DIR}/src" CACHE PATH "Path to oatpp module directory (sources)" FORCE)
set(OATPP_DIR_LIB "${oatpp_BINARY_DIR}/src" CACHE PATH "Path to directory with liboatpp" FORCE)

FetchContent_MakeAvailable(oatpp-postgresql)

# ============================================
# Hiredis (Redis client)
# ============================================

# Try to find installed hiredis via pkg-config
find_package(PkgConfig QUIET)
set(HIREDIS_FOUND FALSE)
if(PkgConfig_FOUND)
    pkg_check_modules(HIREDIS_PKG QUIET hiredis)
    if(HIREDIS_PKG_FOUND)
        set(HIREDIS_FOUND TRUE)
        set(HIREDIS_LIBRARIES ${HIREDIS_PKG_LIBRARIES})
        set(HIREDIS_INCLUDE_DIRS ${HIREDIS_PKG_INCLUDE_DIRS})
        set(HIREDIS_LIBRARY_DIRS ${HIREDIS_PKG_LIBRARY_DIRS})
    endif()
endif()

# If not found via pkg-config, try find_library
if(NOT HIREDIS_FOUND)
    find_library(HIREDIS_LIBRARY
        NAMES hiredis libhiredis
        PATHS
            /usr/local/lib
            /usr/lib
            /opt/homebrew/lib
            /usr/local/Cellar/hiredis/*/lib
    )
    
    find_path(HIREDIS_INCLUDE_DIR
        NAMES hiredis/hiredis.h
        PATHS
            /usr/local/include
            /usr/include
            /opt/homebrew/include
            /usr/local/Cellar/hiredis/*/include
    )
    
    if(HIREDIS_LIBRARY AND HIREDIS_INCLUDE_DIR)
        set(HIREDIS_FOUND TRUE)
        set(HIREDIS_LIBRARIES ${HIREDIS_LIBRARY})
        set(HIREDIS_INCLUDE_DIRS ${HIREDIS_INCLUDE_DIR})
    endif()
endif()

# If still not found, use FetchContent
if(NOT HIREDIS_FOUND)
    FetchContent_Declare(
        hiredis
        GIT_REPOSITORY https://github.com/redis/hiredis.git
        GIT_TAG v1.2.0
    )
    FetchContent_MakeAvailable(hiredis)
    
    # Configure hiredis as static library
    set(HIREDIS_LIBRARIES hiredis_static)
    set(HIREDIS_INCLUDE_DIRS ${hiredis_SOURCE_DIR})
endif()

# ============================================
# gRPC (for future Python integration)
# ============================================

# Currently commented out, can be uncommented when needed
# find_package(gRPC QUIET)
# if(NOT gRPC_FOUND)
#     message(STATUS "gRPC not found, skipping gRPC support")
# endif()

# ============================================
# Project Structure
# ============================================

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

# Collect all source files
file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/main.cpp"
)

file(GLOB_RECURSE HEADERS
    "${CMAKE_SOURCE_DIR}/include/*.hpp"
)

# ============================================
# Executable
# ============================================

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS}
        src/service/TestService.cpp)

# Apply strict warnings only to our code (not dependencies)
# In Debug mode, treat warnings as errors for our code
# Exclude some warnings that appear in Oat++ dependencies
#target_compile_options(${PROJECT_NAME} PRIVATE
#    $<$<CONFIG:Debug>:-Werror>
#    $<$<CONFIG:Debug>:-Wno-pessimizing-move>  # Oat++ uses std::move on temporaries
#    $<$<CONFIG:Debug>:-Wno-sign-compare>      # Oat++ compares signed/unsigned types
#)

# Define OATPP_SWAGGER_RES_PATH for Swagger resources
target_compile_definitions(${PROJECT_NAME} PRIVATE OATPP_SWAGGER_RES_PATH="${OATPP_SWAGGER_RES_PATH}")

# When using FetchContent with add_subdirectory, use 'oatpp' not 'oatpp::oatpp'
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    oatpp
    PRIVATE
    oatpp-swagger
    PRIVATE
    oatpp-postgresql
    PRIVATE
    ${HIREDIS_LIBRARIES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${HIREDIS_INCLUDE_DIRS}
)

# Add library directories for hiredis if found via pkg-config
if(DEFINED HIREDIS_LIBRARY_DIRS)
    link_directories(${HIREDIS_LIBRARY_DIRS})
endif()

# ============================================
# IDE Settings
# ============================================

# File grouping in IDE
source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

# ============================================
# Tests (placeholder for future)
# ============================================

# Enable tests if Google Test is available
# option(BUILD_TESTS "Build tests" OFF)
# if(BUILD_TESTS)
#     enable_testing()
#     add_subdirectory(tests)
# endif()

# ============================================
# Installation
# ============================================

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

message(STATUS "=== Configuration Summary ===")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
if(DEFINED oatpp_SOURCE_DIR)
    message(STATUS "Oat++: ${oatpp_SOURCE_DIR}")
endif()
if(DEFINED oatpp-postgresql_SOURCE_DIR)
    message(STATUS "Oat++ PostgreSQL: ${oatpp-postgresql_SOURCE_DIR}")
endif()
if(DEFINED oatpp-swagger_SOURCE_DIR)
    message(STATUS "Oat++ Swagger: ${oatpp-swagger_SOURCE_DIR}")
endif()
if(DEFINED HIREDIS_INCLUDE_DIRS)
    message(STATUS "Hiredis: ${HIREDIS_INCLUDE_DIRS}")
endif()
message(STATUS "============================")
