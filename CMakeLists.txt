cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_CXX_FLAGS "-std=c++11 -w")
project(comm-server-engine)

# Boost
find_package(Boost REQUIRED)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif ()

include_directories(
    inc
    src
    3rd/curl/include
	3rd/protobuf/include
	3rd/cpp-driver/include)

link_directories("3rd/lib/")

file(GLOB SRC
        model/*.proto
        api/*.proto
        inc/*.cpp
        inc/commons/*.cpp
        inc/mnp/*.cpp
        src/*.cpp
        src/core/*.cpp
        src/logger/*.cpp
        src/logger/spdlog/*.cpp
        src/logger/vt-glog/*.cpp
        src/tcp/*.cpp
        )

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} ${LIBSPDLOG})

set(SYS_LIBS glog nghttp2 ssl crypto boost_system boost_chrono boost_filesystem
boost_regex pthread cppcms booster protobuf curl hiredis)
foreach (LIB ${SYS_LIBS})
    find_library(${LIB} ${LIB})
    if (${LIB})
        target_link_libraries(${PROJECT_NAME} ${LIB})
    else ()
        message(FATAL_ERROR "Can't find ${LIB} library")
    endif ()
endforeach ()
