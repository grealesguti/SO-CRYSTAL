cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(sim)

find_package(Geant4 REQUIRED ui_all vis_all)
#find_package(MPI REQUIRED)

### Gmsh :https://onelab.info/pipermail/gmsh/2013/008279.html
find_library(GMSH_LIB Gmsh PATH_SUFFIXES lib)
find_path(GMSH_INC "Gmsh.h" PATH_SUFFIXES include gmsh include/gmsh)
if(GMSH_LIB AND GMSH_INC)
  # use ${GMSH_LIB} and ${GMSH_INC}
endif(GMSH_LIB AND GMSH_INC)


add_definitions(-DOMPI_SKIP_MPICXX)

include_directories(SYSTEM ${MPI_INCLUDE_PATH})
include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src_G4/*.cc)

file(GLOB headers ${PROJECT_SOURCE_DIR}/src_G4/*.hh)

file(GLOB MACRO_FILES
    "*.mac"
)
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

file(GLOB DATA_FILES
    "data/*.dat"
)

file(COPY ${DATA_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(LYSObarsim sim.cc ${sources} ${headers})
target_link_libraries(LYSObarsim ${MPI_C_LIBRARIES} ${CMAKE_DL_LIBS} ${Geant4_LIBRARIES} -lgmsh)

add_custom_target(Simulation_Guillermo DEPENDS sim)
