cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)

set(
  HUNTER_CACHE_SERVERS
  "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
  CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

huntergate(
  URL "https://github.com/ruslo/hunter/archive/v0.23.34.tar.gz"
  SHA1 "70287b1ffa810ee4e952052a9adff9b4856d0d54"
)


project(template)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

hunter_add_package(Boost COMPONENTS date_time )
find_package(Boost CONFIG REQUIRED date_time)

add_executable(Blockchain_kursovaya project/main.cpp
               project/server/main_server.cpp
               Block.h Block.cpp Sha256.cpp Sha256.h Blockchain.h Blockchain.cpp  trusted_comp.h trsuted_comp.cpp
               rsa.h hugeint.h  cryptkey.h exceptions.h hugeint.cpp rsa.cpp client.h)


target_link_libraries(Blockchain_kursovaya GTest::main Boost::date_time)

