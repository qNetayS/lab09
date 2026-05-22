cmake_minimum_required(VERSION 3.10)
project(print)

set(CMAKE_CXX_STANDARD 11)

add_library(print STATIC print.cpp)
install(TARGETS print DESTINATION lib)
install(FILES print.h DESTINATION include)

# Настройки для CPack (упаковка)
set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_NAME "print")
set(CPACK_PACKAGE_VERSION "0.1.0")
include(CPack)
