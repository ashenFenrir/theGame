cmake_minimum_required(VERSION 3.11)#set min version of cmake

include(FetchContent)

project(theGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	0af55ccecd98d4e5a8d1fad7de25ba429d60e863 #refs/tags/1.0.1
)
FetchContent_MakeAvailable(glm)

set(IMGUI_VERSION 1.92.5)
FetchContent_Declare(
    imgui
    URL https://github.com/ocornut/imgui/archive/refs/tags/v${IMGUI_VERSION}-docking.tar.gz
)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC 
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)

target_include_directories(imgui 
    PUBLIC 
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
    PRIVATE
        ${imgui_SOURCE_DIR}
)

target_include_directories(imgui INTERFACE ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PNG)

include_directories(${SDL3_INCLUDE_DIRS})

#collect all source files
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)#hpp
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)#cpp
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})#add all source files

add_subdirectory(libs/glad)

target_link_libraries(${PROJECT_NAME} ${SDL3_LIBRARIES} ${OPENGL_LIBRARIES} glad glm::glm imgui png)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)





# set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


# include_directories(libs ${PROJECT_SOURCE_DIR}/libs/glew/include)

# #link include folder
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw)
# add_subdirectory( ${PROJECT_SOURCE_DIR}/libs/glew/build/cmake)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)

# target_link_libraries(${PROJECT_NAME} glew glfw OpenGL::GL glm)
