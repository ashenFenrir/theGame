# glad/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(glad LANGUAGES C)

# Set source files
set(GLAD_SOURCES
    src/glad.c
)

# Set include directories
set(GLAD_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Create glad library
add_library(glad ${GLAD_SOURCES})

# Set include directories for glad target
target_include_directories(glad PUBLIC ${GLAD_INCLUDES})

# Set C standard (optional but good practice)
set_target_properties(glad PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
)

# If you need specific compiler flags
# if(MSVC)
#     target_compile_definitions(glad PRIVATE _CRT_SECURE_NO_WARNINGS)
# endif()

# Optional: Mark as interface library if you only have headers
# add_library(glad INTERFACE)
# target_include_directories(glad INTERFACE ${GLAD_INCLUDES})