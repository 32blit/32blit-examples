
cmake_minimum_required(VERSION 3.9...3.26)
project (saves)
find_package (32BLIT CONFIG REQUIRED PATHS ../..)

blit_executable (saves saves.cpp)
blit_metadata (saves metadata.yml)
