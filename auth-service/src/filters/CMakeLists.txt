cmake_minimum_required(VERSION 3.5)

# Puts source files here
set(FILTER_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/JWTFilter.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/SignUpFilter.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/SignInFilter.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/ConfirmOtpFilter.cc
)

# Puts header files here
set(FILTER_HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/JWTFilter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SignUpFilter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SignInFilter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ConfirmOtpFilter.h
)

target_sources(${PROJECT_NAME}
	       PRIVATE
	       ${FILTER_SOURCES}
	       ${FILTER_HEADERS} # for VS integration
)