cmake_minimum_required(VERSION 3.20)

project(CryptoArb CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENTIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_EXPORT_COMPILE_COMMANDS: ${CMAKE_EXPORT_COMPILE_COMMANDS}")
message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# CURL
find_package(CURL REQUIRED)

# OpenSSL
set(OPENSSL_ROOT_DIR "/opt/homebrew/opt/openssl@3")
find_package(OpenSSL REQUIRED)

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

file(GLOB SOURCES
      src/*.h
      src/*.cpp
      # src/exchanges/*.cpp src/exchanges/*.h src/coins/*.cpp src/coins/*.h src/utils/*.h src/utils/*.cpp
      )

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
                           ${PROJECT_SOURCE_DIR}/src
                           ${CURL_INCLUDE_DIR}
                           ${OPENSSL_INCLUDE_DIR}
                           )

target_link_libraries(${PROJECT_NAME}
                      ${CURL_LIBRARIES}
                      ${OPENSSL_LIBRARIES}
                      )

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/..)
