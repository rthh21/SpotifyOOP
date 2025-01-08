cmake_minimum_required(VERSION 3.28)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
project(player)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


###############################################################################

list(APPEND CMAKE_PREFIX_PATH ../libs/SDL2/cmake/sdl2-config.cmake)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
file(GLOB SRC "src/*.cpp")

add_executable(${PROJECT_NAME}
    main.cpp
    generated/src/Helper.cpp
    env_fixes.h 
    ${SRC}
)

include(cmake/CompilerFlags.cmake)

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE generated/include)
include_directories(${PROJECT_NAME} SYSTEM PRIVATE libs/SDL2/include libs/SDL2_Mixer/include)
###############################################################################
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/headers)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/music)

link_directories(${PROJECT_NAME} libs/SDL2/lib libs/SDL2_Mixer/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2_mixer)

###############################################################################

install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

include(cmake/CopyHelper.cmake)
copy_files(FILES state.txt SDL2.dll SDL2_mixer.dll)
copy_files(DIRECTORY music)
