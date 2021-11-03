# CMakeList.txt : CMake project for CSwigPython, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CSwigPython")

add_compile_definitions(SWIG_PYTHON_INTERPRETER_NO_DEBUG)
find_package (Python3 COMPONENTS Interpreter REQUIRED)
find_package (PythonLibs REQUIRED)

# Add source to this project's executable.
add_library (_test SHARED "Test_wrap.cxx" "Test.cpp")
add_executable (testapp "CSwigPython.cpp" "Test.cpp")

target_include_directories (_test PUBLIC ${PYTHON_INCLUDE_DIRS})
target_link_libraries (_test PUBLIC ${PYTHON_LIBRARIES})

set_target_properties(_test PROPERTIES SUFFIX ".pyd")

# TODO: Add tests and install targets if needed.
