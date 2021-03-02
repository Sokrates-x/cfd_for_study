add_library(libUEquation u_equation.cxx)

target_link_libraries(libUEquation PUBLIC libEquation)

target_include_directories(libUEquation PUBLIC
									"${PROJECT_SOURCE_DIR}/equation"
									)
