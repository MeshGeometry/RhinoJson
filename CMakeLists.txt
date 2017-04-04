cmake_minimum_required (VERSION 2.8.6)

project (RhinoJson C CXX)

#build create OpenNurbs
#must use cmake branch of this submodule
#add_subdirectory("./opennurbs")

#try just flat out including everything
#define source
file(GLOB OPENNURBS_SRC
    "./opennurbs/*.h"
    "./opennurbs/*.cpp")

file(GLOB ZLIB_SRC
    "./opennurbs/zlib/*.h"
    "./opennurbs/zlib/*.c")

#now create RhinoJson app
include_directories("./opennurbs/zlib")
include_directories("./opennurbs")
include_directories("./rapidjson/include/rapidjson")
add_executable(RhinoJson "main.cpp" ${OPENNURBS_SRC} ${ZLIB_SRC})

if(MSVC)
	#remove the win32 define
	message(${CMAKE_CXX_FLAGS})
	string (REPLACE "/DWIN32" "/DWIN64" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}) 
	message(${CMAKE_CXX_FLAGS})
	add_definitions(-DUNICODE -D_UNICODE -DON_COMPILING_OPENNURBS)
endif()

#link
# target_link_libraries(RhinoJson zlib)
# target_link_libraries(RhinoJson OpenNurbs)