cmake_minimum_required(VERSION 3.11)

include(cmake/project-settings.cmake)

project(AuthService 
	VERSION 1.0.0
	DESCRIPTION "Authentification service"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(UTILS_DIR ${PROJECT_SOURCE_DIR}/utils)

#include(cmake/static-analyzers.cmake)
#AuthService_enable_lint()

add_subdirectory(src)

file(GLOB_RECURSE ALL_SOURCE_FILES *.cc *.h)
foreach (SOURCE_FILE ${ALL_SOURCE_FILES})
  string(FIND ${SOURCE_FILE} ${THIRDPARTY_DIR} THIRDPARTY_DIR_FOUND)
  if (NOT ${THIRDPARTY_DIR_FOUND} EQUAL -1)
    list(REMOVE_ITEM ALL_SOURCE_FILES ${SOURCE_FILE})
  endif()
endforeach()

include(cmake/hooks/format.cmake)
AuthService_enable_target_format(${ALL_SOURCE_FILES})

include(cmake/hooks/lint.cmake)
AuthService_enable_target_lint(${ALL_SOURCE_FILES})

include(cmake/hooks/docker-build.cmake)
AuthService_enable_target_docker_build(${DOCKER_ID} ${DOCKER_REPO} ${DOCKER_TAG})

include(cmake/hooks/docker-push.cmake)
AuthService_enable_target_docker_push(${DOCKER_ID} ${DOCKER_REPO} ${DOCKER_TAG})
