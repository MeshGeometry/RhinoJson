cmake_minimum_required (VERSION 2.8.6)

project (RhinoJson C CXX)

#build create OpenNurbs
#must use cmake branch of this submodule
add_subdirectory("./opennurbs")

#now create RhinoJson app
include_directories("./opennurbs")
include_directories("./rapidjson/include/rapidjson")
add_executable(RhinoJson "main.cpp")

#link
target_link_libraries(RhinoJson OpenNurbsLib)