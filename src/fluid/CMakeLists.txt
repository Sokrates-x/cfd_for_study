add_library(libFluid fluid.cxx)

target_link_libraries(libFluid PUBLIC libField)

target_include_directories(libFluid PUBLIC
									"${PROJECT_SOURCE_DIR}/field"
									)
