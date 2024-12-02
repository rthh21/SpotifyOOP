cmake_minimum_required(VERSION 3.28)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
project(oop)
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)

###############################################################################

list(APPEND CMAKE_PREFIX_PATH ../libs/SDL2/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)


#if(WIN32)
    # On Windows, specify the path to SDL2 and SDL2_mixer manually if necessary
 #   set(SDL2_DIR "C:/msys64/ucrt64/lib/cmake/SDL2")
  #  set(SDL2_MIXER_DIR "C:/msys64/ucrt64/lib/cmake/SDL2_mixer")

    # Add search paths for MinGW and MSYS2 libraries
   # link_directories("C:/msys64/ucrt64/lib")
#elseif(APPLE)
    # Mac-specific setup, if you use brew for SDL2 and SDL2_mixer
 #   find_package(SDL2 REQUIRED HINTS /usr/local/lib/cmake/SDL2)
  #  find_package(SDL2_mixer REQUIRED HINTS /usr/local/lib/cmake/SDL2_mixer)
#elseif(UNIX)
    # Linux-specific configuration, assuming SDL2 and SDL2_mixer are installed
 #   find_package(SDL2 REQUIRED)
  #  find_package(SDL2_mixer REQUIRED)
#endif()


###############################################################################

# external dependencies with FetchContent
# include(FetchContent)
#
# set(FETCHCONTENT_QUIET OFF)
# set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
#
# NOTE: Also update env vars used for caching in
#         - .github/actions/configure-cmake/action.yml
#         - .github/workflows/cmake.yml
# FetchContent_Declare(
#         SomeLib
#         GIT_REPOSITORY https://github.com/<SomeUser>/<SomeLib>.git
#         GIT_TAG        <some_git_hash> # <which tag/branch @ <some_date>>
#         GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
# )
#
# FetchContent_MakeAvailable(SomeLib)

###############################################################################

# external dependencies with find_package

# find_package(Threads REQUIRED)

###############################################################################

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
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE libs/SDL2/include libs/SDL2_Mixer/include)
###############################################################################
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/headers)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/music)

 
target_link_directories(${PROJECT_NAME} PRIVATE libs/SDL2/lib libs/SDL2_Mixer/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2_mixer)
# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${<SomeLib>_SOURCE_DIR}/include)
# target_link_directories(${PROJECT_NAME} PRIVATE ${<SomeLib>_BINARY_DIR}/lib)
# target_link_libraries(${PROJECT_NAME} <SomeLib>)

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

include(cmake/CopyHelper.cmake)
copy_files(FILES tastatura.txt SDL2.dll SDL2_mixer.dll)
copy_files(DIRECTORY music)
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds)
# copy_files(DIRECTORY images sounds)
