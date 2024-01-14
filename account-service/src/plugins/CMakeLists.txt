cmake_minimum_required(VERSION 3.5)

# Puts source files here
set(PLUGINS_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/JWTPlugin.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/SMTPMailPlugin.cc
)

# Puts header files here
set(PLUGINS_HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/JWTPlugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SMTPMailPlugin.h
)

target_sources(${PROJECT_NAME}
	       PRIVATE
	       ${PLUGINS_SOURCES}
	       ${PLUGINS_HEADERS} # for VS integration
)