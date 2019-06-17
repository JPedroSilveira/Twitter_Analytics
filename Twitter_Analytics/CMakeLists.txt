cmake_minimum_required(VERSION 3.12)
project(Twitter_Analytics C)

set(CMAKE_C_STANDARD 11)

include_directories(Header)

add_executable(Twitter_Analytics
        Header/avl.h
        Header/BinaryTree.c
        Header/BinaryTree.h
        Header/File.h
        Header/List.h
        Header/ops.h
        Header/Tweet.h
        Source/avl.c
        Source/File.c
        Source/List.c
        Source/Tweet.c
        Source/generic.c
        Header/generic.h

        TwitterAnalytics.c)
