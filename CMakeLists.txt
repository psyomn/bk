cmake_minimum_required(VERSION 3.9)
project(bk)

# Took some many of these parts for cmake off
#   https://github.com/RAttab/optics

enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wswitch-enum -Wwrite-strings -Wunreachable-code -Wno-strict-aliasing")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format-nonliteral -Wno-missing-field-initializers")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -g -O3 -Werror -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -std=gnu++17")

set(bk_SOURCES
  src/helper.cc)

add_library(libbk STATIC ${bk_SOURCES})

include_directories(include)

add_executable(bk src/main.cc ${bk_SOURCES})
target_link_libraries(bk libbk)

function(bk_add_test name)
  add_executable(${name} test/${name}.cc)
  target_link_libraries(${name} libbk)
  add_test(
    NAME    ${name}_valgrind
    COMMAND valgrind --leak-check=full
                     --error-exitcode=1 $<TARGET_FILE:${name}>)
  add_test(${name} ${name})
endfunction(bk_add_test)

bk_add_test(bk_example)
