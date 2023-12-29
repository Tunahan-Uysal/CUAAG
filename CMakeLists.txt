cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_C_STANDARD 99)

# Add your source files
add_executable(${PROJECT_NAME} src/main.c includes/image.c includes/ascii.c)

# Set the compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE -lm -fsanitize=address -Wall)

# Specify the directories to find header files
target_include_directories(${PROJECT_NAME} PUBLIC includes)

# Link the necessary libraries
# You may need to adjust this depending on your project's requirements
target_link_libraries(${PROJECT_NAME} PRIVATE )
