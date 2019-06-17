cmake_minimum_required(VERSION 3.12)
project(TrabFinal C)

set(CMAKE_C_STANDARD 11)

include_directories(Twitter_Analytics/Header)

add_executable(TrabFinal
        Twitter_Analytics/Header/avl.h
        Twitter_Analytics/Header/BinaryTree.h
        Twitter_Analytics/Header/File.h
        Twitter_Analytics/Header/List.h
        Twitter_Analytics/Header/ops.h
        Twitter_Analytics/Header/Tweet.h
        Twitter_Analytics/Header/generic.h
        Twitter_Analytics/Header/avl.h

        Twitter_Analytics/Source/BinaryTree.c
        Twitter_Analytics/Source/avl.c
        Twitter_Analytics/Source/File.c
        Twitter_Analytics/Source/List.c
        Twitter_Analytics/Source/Tweet.c
        Twitter_Analytics/Source/generic.c
        Twitter_Analytics/Source/avl.c
        Twitter_Analytics/TwitterAnalytics.c)
