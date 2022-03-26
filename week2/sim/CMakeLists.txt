cmake_minimum_required(VERSION 2.6 FATAL_ERROR)   #CMake version

project(Simulation)                               #Project name

find_package(Geant4 REQUIRED ui_all vis_all)      #Packages used

include(${Geant4_USE_FILE})                       #Including Geant4 software

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)     #Define source file format
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)     #Define header file format

add_executable(sim sim.cc ${sources} ${headers})  #Define executable file and path

target_link_libraries(sim ${Geant4_LIBRARIES})    #Sourcing the libraries

add_custom_target(Simulation DEPENDS sim)         #Project depends od executable
