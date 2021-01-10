cmake_minimum_required(VERSION 3.3)

project(captureflag_python)

option(CXX "enable C++ compilation" ON)
if(CXX)
    enable_language(CXX)
endif()

set(CMAKE_CXX_STANDARD 11)

# find_package(PythonLibs 3.7 REQUIRED)
find_package(Python COMPONENTS Interpreter NumPy)
include(FindPythonLibs)

# message("PYTHON_EXECUTABLE = ${PYTHON_EXECUTABLE}")
# execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "import os; os.environ['DISTUTILS_USE_SDK']='1'; import numpy; print(numpy.distutils.misc_util.get_numpy_include_dirs()[0])"
#    OUTPUT_VARIABLE PYTHON_NUMPY_INCLUDE_DIRS
#   )

include_directories(
    ${PYTHON_INCLUDE_DIRS}
  )
message("${PYTHON_INCLUDE_DIRS} and ${PYTHON_NUMPY_INCLUDE_DIRS}")

set(SRC_DIR src/)
add_executable(c_call_py_main c_call_py_main.cpp)
target_link_libraries(c_call_py_main ${PYTHON_LIBRARIES} Python::NumPy)



