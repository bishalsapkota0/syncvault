cmake_minimum_required(VERSION 3.16)
project(SyncVault LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE AND NOT OPENSSL_ROOT_DIR)
  set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl@4)
endif()
find_package(OpenSSL REQUIRED)

add_executable(syncvault
  src/main.cpp
  src/common/Hasher.cpp
  src/common/RollingHash.cpp
  src/common/Chunker.cpp
  src/common/Dedup.cpp
)

target_link_libraries(syncvault PRIVATE OpenSSL::Crypto)
