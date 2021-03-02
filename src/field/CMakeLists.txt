add_library(libField field.cxx)

target_link_libraries(libField PUBLIC libUnit)

target_include_directories(libField PUBLIC
									"${PROJECT_SOURCE_DIR}/unit"
									)
