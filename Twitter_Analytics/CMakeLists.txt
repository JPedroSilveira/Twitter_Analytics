cmake_minimum_required(VERSION 3.12)
project(Twitter_Analytics C)

set(CMAKE_C_STANDARD 11)

include_directories(Header)

add_executable(Twitter_Analytics
        Header/AVL.h
        Header/File.h
        Header/Generic.h
        Header/List.h
        Header/OPES.h
        Header/Tweet.h
        Source/AVL.c
        Source/BinaryTree.c
        Source/File.c
        Source/Generic.c
        Source/List.c
        Source/Tweet.c
        TwitterAnalytics.c)

