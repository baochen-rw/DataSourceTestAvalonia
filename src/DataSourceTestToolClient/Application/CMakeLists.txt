cmake_minimum_required(VERSION 3.10)
project(DataSourceTestTool)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define Windows version for networking
if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()

# Find Boost
find_package(Boost REQUIRED COMPONENTS system)

# Create executable
add_executable(DataSourceTestTool
    src/main.cpp
    src/application.cpp
    src/network_client.cpp
)

# Link libraries
target_link_libraries(DataSourceTestTool ${Boost_LIBRARIES})
target_include_directories(DataSourceTestTool PRIVATE ${Boost_INCLUDE_DIRS})

# Windows networking
if(WIN32)
    target_link_libraries(DataSourceTestTool ws2_32 wsock32)
endif()
