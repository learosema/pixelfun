cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

include(cmake/AppleBuild.cmake)

project(
  PixelfFun
  DESCRIPTION "Base gui project setup with SDL2 and OpenGL."
  VERSION 1.0.0
  LANGUAGES C CXX)

set(PROJECT_COMPANY_NAME "Lea Codes")
set(PROJECT_COMPANY_NAMESPACE "codes.lea")  # Reverse domain name notation

include(cmake/StandardProjectSettings.cmake)
include(GNUInstallDirs)

# Link this "library" to use the warnings specified in CompilerWarnings.cmake.
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

enable_testing()

add_subdirectory(packaging)
add_subdirectory(vendor)
add_subdirectory(src)
