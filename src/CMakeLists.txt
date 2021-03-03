# cmake version
cmake_minimum_required(VERSION 3.10)

# set project name 
project(cfd_fs VERSION 1.0)

# set the executable
add_executable(cfd_fs main.cxx)

# the config files
configure_file(config.h.in config.h)

# c++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED Ture)

# add directory
add_subdirectory(bc)
add_subdirectory(fluid)
add_subdirectory(field)
add_subdirectory(time)
add_subdirectory(equation)
add_subdirectory(unit)
add_subdirectory(mesh)

# links
target_link_libraries(cfd_fs PUBLIC
							libBoundaryConditions
							libFluid
							libField
							libRhoEquation
							libUEquation
							libTimeCfd
							)
# includes
target_include_directories(cfd_fs PUBLIC
									"${PROJECT_BINARY_DIR}"
									"${PROJECT_SOURCE_DIR}/bc"	
									"${PROJECT_SOURCE_DIR}/time"
									"${PROJECT_SOURCE_DIR}/unit"
									"${PROJECT_SOURCE_DIR}/field"
									"${PROJECT_SOURCE_DIR}/fluid"
									"${PROJECT_SOURCE_DIR}/mesh"
									"${PROJECT_SOURCE_DIR}/equation/uEquation"
								   "${PROJECT_SOURCE_DIR}/equation/rhoEquation"	
									)
