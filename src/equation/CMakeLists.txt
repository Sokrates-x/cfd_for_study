add_library(libEquation equation.cxx)

add_subdirectory(rhoEquation)
add_subdirectory(uEquation)

target_link_libraries(libEquation PUBLIC
							libMesh
							libTimeCfd
							libBoundaryConditions
							libFluid
							)

target_include_directories(libEquation PUBLIC
									"${PROJECT_SOURCE_DIR}/mesh"
									"${PROJECT_SOURCE_DIR}/time"
									"${PROJECT_SOURCE_DIR}/bc"
									"${PROJECT_SOURCE_DIR}/fluid"
									)
