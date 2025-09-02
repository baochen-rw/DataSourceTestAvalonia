cmake_minimum_required(VERSION 3.10)
project(DataSourceTestToolClient)

# Set C++ standard to C++17 (required by Kanzi)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add library directory
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/bin)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Find Boost
find_package(Boost REQUIRED COMPONENTS system iostreams)

# Build from source code - ONLY the essential files
add_executable(DataSourceTestToolClient 
    src/Main.cpp
    src/TestToolApplication.cpp
    src/datasourcetesttoolclient.cpp
)

# Link with Boost
target_link_libraries(DataSourceTestToolClient ${Boost_LIBRARIES})
target_include_directories(DataSourceTestToolClient PRIVATE ${Boost_INCLUDE_DIRS})

# Link with Kanzi DLLs - use the runtime libraries directly
target_link_libraries(DataSourceTestToolClient 
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/kzcoreui_GL_vs2015_Release.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/kzui_GL_vs2015_Release.dll  
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/kzjs_GL_vs2015_Release.dll
)

# Set working directory for Visual Studio debugging
set_target_properties(DataSourceTestToolClient PROPERTIES 
    VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)

# Copy all necessary DLLs to output directory for runtime
add_custom_command(TARGET DataSourceTestToolClient POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
            ${CMAKE_CURRENT_SOURCE_DIR}/bin/ 
            $<TARGET_FILE_DIR:DataSourceTestToolClient>
    COMMENT "Copying runtime dependencies"
)
