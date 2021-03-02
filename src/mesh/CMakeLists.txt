add_library(libMesh mesh.cxx)

add_subdirectory(node)

target_link_libraries(libMesh PUBLIC libNode)

target_include_directories(libMesh PUBLIC
									"${PROJECT_SOURCE_DIR}/mesh/node"
									)
