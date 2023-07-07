# minimum CMake version (minimum feature)
cmake_minimum_required(VERSION 3.12)

# Add name on project 
project(cpp-coso VERSION "0.3.1")

set(GITHUB_USERNAME "MGuillaumeF")
set(CPACK_PACKAGE_VENDOR "${GITHUB_USERNAME}")
set(CPACK_PACKAGE_CONTACT "mguillaumef@gmail.com")
set(COMPANY_NAME "")
set(LEGAL_COPYRIGHT "")

# Create application executable files
set(APPLICATION_NAME ${PROJECT_NAME})
set(APPLICATION_DESCRIPTION "cpp reports to sonarqube converter")

# define C++ version on standard
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  MESSAGE("Debug mode activate test")
  # activate test on project
  enable_testing()
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
  MESSAGE("Compiler used is Clang")
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage --coverage")
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ftest-coverage -lgcov --coverage")
  else ()
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O")
  endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  MESSAGE("Compiler used is g++")
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra -pedantic -Wformat -Wformat-security -Winit-self -Wparentheses -Wsequence-point -Wreturn-type -Wunknown-pragmas -Wfloat-equal -Wtype-limits -Woverlength-strings -Waddress")
  SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -ftest-coverage -lgcov --coverage")
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage --coverage")
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ftest-coverage -lgcov --coverage")
  else ()
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O")
  endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  # using Intel C++
  MESSAGE("Compiler used is Intel")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
  MESSAGE("Compiler used is Microsoft Visual Studio C++")
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20 /Wall /Zi /D_CRT_NONSTDC_NO_DEPRECATE /D_CRT_SECURE_NP_DEPRECATE /DNOMINMAX")
  SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}") 
  #/EHsc /MD
endif()

# Add all tests files in TESTS_SRC_UT_DIR variable
file(GLOB_RECURSE TESTS_SRC_UT_DIR CONFIGURE_DEPENDS
     "test/ut/*.hpp"
     "test/ut/*.cpp"
)

# Add all Report files in REPORT_SRC_DIR variable
file(GLOB_RECURSE REPORT_SRC_DIR CONFIGURE_DEPENDS
     "src/report/*.hpp"
     "src/report/*.cpp"
     "src/Application.hpp"
     "src/Application.cpp"
)

find_package (Threads)
set(Boost_USE_STATIC_LIBS ON)
# search external dependence BOOST
find_package (Boost COMPONENTS system filesystem REQUIRED)
if (Boost_FOUND)
  # Specify the configuration file from which the header file will be generated
  configure_file (config.hpp.in config.hpp @ONLY)
 
  # add a directory with header files to see the generated file
  include_directories (${CMAKE_CURRENT_BINARY_DIR})
 
  # add boost includes
  include_directories(${Boost_INCLUDE_DIRS}) 
  # Create application executable files
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/versioninfo.rc.cmake.in versioninfo.rc @ONLY)
  set(APP_ICO_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")
  add_executable(${PROJECT_NAME} ${REPORT_SRC_DIR} "src/main.cpp" "${CMAKE_CURRENT_BINARY_DIR}/versioninfo.rc" ${APP_ICO_RESOURCE})
  install(TARGETS cpp-coso DESTINATION cpp-coso)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(cpp-cosoTest ${TESTS_SRC_UT_DIR} ${REPORT_SRC_DIR})
    # when run mannualy (next to the target)
    add_custom_command(TARGET cpp-cosoTest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/test/resources $<TARGET_FILE_DIR:cpp-cosoTest>/resources)
    # when run with ctest (cwd of run of ctest)
    add_custom_command(TARGET cpp-cosoTest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/test/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)
    add_test(cpp-cosoUnitTests cpp-cosoTest --show_progress=yes --log_level=all --log_format=XML --report_level=detailed --report_format=XML --log_sink=${CMAKE_SOURCE_DIR}/reports/reports.xml  --report_sink=${CMAKE_SOURCE_DIR}/reports/reportUT.xml) 
  endif() 
  if(WIN32)
    add_definitions("-D_WIN32_WINNT=0x0601")
    target_link_libraries(cpp-coso ${Boost_LIBRARIES} wsock32 ws2_32 ${EXTERNAL_LIBS} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
      target_link_libraries(cpp-cosoTest ${Boost_LIBRARIES} wsock32 ws2_32 ${EXTERNAL_LIBS} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
    endif()
  else ()
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    target_link_libraries(cpp-coso ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
      target_link_libraries(cpp-cosoTest ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
    endif()
  endif()
else ()
  # If boost not found print fatal error message
  message(FATAL_ERROR "Boost not found")
endif ()

# CPACK DEFINITION
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "cpp-coso")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${APPLICATION_DESCRIPTION}")
# set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/docs/README.txt")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}-${CMAKE_PROJECT_VERSION}")
if(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full UNIX paths properly.
  # Make sure there is at least one set of four backlashes.
  # set(CPACK_PACKAGE_ICON "resources\\\\icon/cpp-coso/cpp-coso.bmp")
  # set(CPACK_NSIS_MUI_ICON "icon.ico")
  set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\cpp-coso.exe")
  set(CPACK_NSIS_DISPLAY_NAME "${PROJECT_NAME} ${CMAKE_PROJECT_VERSION} cpp reports to sonarqube converter")
  set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.github.com/MGuillaumeF")
  set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.github.com/MGuillaumeF")
  set(CPACK_NSIS_CONTACT "${CPACK_PACKAGE_CONTACT}")
  set(CPACK_NSIS_MODIFY_PATH ON)
else()
  set(CPACK_STRIP_FILES "bin/cpp-coso")
  set(CPACK_SOURCE_STRIP_FILES "")
endif()
set(CPACK_PACKAGE_EXECUTABLES "cpp-coso" "cpp report to sonarqube report")
include(CPack)
