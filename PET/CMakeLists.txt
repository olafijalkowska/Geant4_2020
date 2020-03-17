cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(PET)

# GEANT4 core
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#ROOT
find_package(ROOT)
include_directories(${ROOT_INCLUDE_DIRS})

set(CMAKE_BUILD_TYPE release)

# User code
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(PET PET.cc ${sources} ${headers})
target_link_libraries(PET ${Geant4_LIBRARIES})
target_link_libraries(PET ${ROOT_LIBRARIES})

