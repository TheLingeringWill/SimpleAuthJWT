cmake_minimum_required(VERSION 3.5)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} MODEL_SOURCES)

target_sources(${PROJECT_NAME}
	       PRIVATE
	       ${MODEL_SOURCES}
)