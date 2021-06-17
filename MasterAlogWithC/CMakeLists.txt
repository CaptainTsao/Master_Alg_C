cmake_minimum_required(VERSION 3.15)

project(MaterAlgoWithC C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_DEBUG "-g -D_DEBUG -O0")
set(CMAKE_C_FLAGS_RELEASE "-g -DNDEBUG -O3")

#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -static -O0 -Wall -g2 -ggdb")
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -static -O3 -Wall")
#SET(CMAKE_BUILD_TYPE "Debug")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(bistree.h
        bistree.c
        bitree.c
        bitree.h
        list.c
        list.h
        traverse.c
        traverse.h
        set.h
        set.c
        frames.h
        frames.c
#        leetcode.h
#        ex_list.c
#        leetcode_109.c
#        bitree_ex.c
#        ex_bitree.c
        queue.c
        queue.h
#        ex_queue.c
        uthash.h
        adlist.c
        adlist.h
        leetcode_113.c
        )