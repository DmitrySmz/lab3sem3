cmake_minimum_required(VERSION 3.27)
project(laba3)

set(CMAKE_CXX_STANDARD 23)

add_executable(laba3 main.cpp
        test_btree.cpp
        test.cpp
        test_hashtable.h
        test_sparse_matrix.h
        test_sparse_vector.h
        interface.cpp
        DataStructures/Histogram.h
        test_histogram.h
)
