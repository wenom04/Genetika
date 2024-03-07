cmake_minimum_required(VERSION 3.11)
project(genetika VERSION 0.1.0 LANGUAGES C CXX)

add_executable(genetika)

target_sources(genetika PRIVATE
genetika_teszt.cpp allapotgep.cpp memtrace.cpp
)
target_compile_options(
    genetika PRIVATE -DMEMTRACE 
)
