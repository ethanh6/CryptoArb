cmake_minimum_required(VERSION 3.20)

project(KryptoArb CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENTIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_EXPORT_COMPILE_COMMANDS: ${CMAKE_EXPORT_COMPILE_COMMANDS}")
message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Catch2 3 REQUIRED)
find_package(CURL)
find_package(Jansson)
find_package(SQLite3)

file(GLOB SOURCES
      src/*.h
      src/*.cpp
      src/exchanges/*.cpp
      src/exchanges/*.h
      src/utils/*.h
      src/utils/*.cpp
      )

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
                           ${PROJECT_SOURCE_DIR}/src
                           ${CURL_INCLUDE_DIR}
                           ${OPENSSL_INCLUDE_DIR}
                           ${JANSSON_INCLUDE_DIR}
                           ${SQLITE3_INCLUDE_DIR}
                           )

target_link_libraries(${PROJECT_NAME}
                      ${CURL_LIBRARIES}
                      ${OPENSSL_LIBRARIES}
                      ${JANSSON_LIBRARIES}
                      ${SQLITE3_LIBRARIES}
                      )

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/..)
