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
               project/sourses/Block.hpp project/sourses/Block.cpp project/sourses/Sha256.cpp project/sourses/Sha256.hpp 
               project/sourses/Blockchain.hpp project/sourses/Blockchain.cpp  project/sourses/trusted_comp.hpp 
               project/sourses/trsuted_comp.cpp project/sourses/rsa.hpp project/sourses/hugeint.hpp  
               project/sourses/cryptkey.hpp project/sourses/exceptions.hpp project/sourses/hugeint.cpp 
               project/sourses/rsa.cpp project/sourses/client.hpp)


target_link_libraries(Blockchain_kursovaya GTest::main Boost::date_time)

