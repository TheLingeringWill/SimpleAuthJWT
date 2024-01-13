if(PROJECT_NAME)
  macro(${PROJECT_NAME}_enable_lint)
    find_program(CLANG_TIDY clang-tidy)
    if(CLANG_TIDY)
      set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
    else()
      message(SEND_ERROR "clang-tidy requested but executable not found")
    endif()
  endmacro()
else()
  message(SEND_ERROR "Project not found")
endif()
