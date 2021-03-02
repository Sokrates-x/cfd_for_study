add_library(libRhoEquation rho_equation.cxx)

target_link_libraries(libRhoEquation PUBLIC
							libEquation
							)

target_include_directories(libRhoEquation PUBLIC
									"${PROJECT_SOURCE_DIR}/equation"
									)
