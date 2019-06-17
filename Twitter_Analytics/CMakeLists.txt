cmake_minimum_required(VERSION 3.12)
project(Twitter_Analytics C)

set(CMAKE_C_STANDARD 11)

include_directories(Header)

add_executable(Twitter_Analytics
        Header/avl.h
        Header/BinaryTree.h
        Header/File.h
        Header/generic.h
        Header/List.h
        Header/ops.h
        Header/Tweet.h
        Source/avl.c
        Source/BinaryTree.c
        Source/File.c
        Source/generic.c
        Source/List.c
        Source/Tweet.c
        TwitterAnalytics.c)
