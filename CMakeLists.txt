# This CMakeLists.txt project is for Ubuntu only
project(redgpu_inline_procedure)
cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_CXX_STANDARD 14)
link_libraries(
  /opt/RedGpuSDK/libredgpu.so
)
add_library(redgpu_inline_procedure SHARED
  redgpu_inline_procedure.cpp
)
