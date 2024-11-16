# CMakeList.txt: First_OpenGL_Proj 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

set(PROJECT_NAME "First_OpenGL_Proj")

project (${PROJECT_NAME} VERSION 0.0.1 LANGUAGES C CXX)

include_directories(${PROJECT_SOURCE_DIR}/include)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src SRC_LIST)
message("SRC_LIST is " ${SRC_LIST})

set(CMAKE_PREFIX_PATH "E:/home/Lib" CACHE STRING "自定义查找包的安装路径" FORCE)

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE TEST_LIST "test/*.cpp")
foreach (name ${TEST_LIST})
    string(REGEX MATCH ".*test/.*" relative_path ${name})
	string(REGEX REPLACE ".*test/" "" target_name ${relative_path})
    string(REGEX REPLACE ".cpp" "" target_name ${target_name})
	message(STATUS "target_name :${target_name}")
	add_executable (${target_name}  ${SRC_LIST} ${name})
	target_link_libraries(${target_name} PRIVATE glfw OpenGL::GL)
endforeach()

set(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resource")

file(GLOB_RECURSE RESOURCE_FILES "${RESOURCE_DIR}/*")

foreach(file ${RESOURCE_FILES})
	string(REGEX MATCH ".*resource/.*" relative_path ${file})
	string(REGEX REPLACE ".*resource/" "" file_relative_path ${relative_path})
	configure_file(${file}  ${CMAKE_CURRENT_BINARY_DIR}/resource/${file_relative_path} COPYONLY)
endforeach()