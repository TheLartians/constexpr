cmake_minimum_required (VERSION 3.0.2)

project (constexprTests)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

if (TEST_INSTALLED_VERSION)
  find_package(constexpr REQUIRED)
else()
  CPMAddPackage(
    NAME constexpr
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
  )
endif()

CPMAddPackage(
  NAME Format.cmake
  GITHUB_REPOSITORY TheLartians/Format.cmake
  VERSION 1.3
)

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable (test_constexpr ${sources})
target_link_libraries(test_constexpr constexpr)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(test_constexpr PUBLIC -Wall -pedantic -Wextra -Werror)
elseif(MSVC)
  target_compile_options(test_constexpr PUBLIC /W4 /WX /wd4348)
  target_compile_definitions(test_constexpr PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
endif()

# ---- add tests ----

ENABLE_TESTING() 
ADD_TEST(ConstExprTests test_constexpr)

# ---- code coverage ----

if (ENABLE_TEST_COVERAGE)
  target_compile_options(test_constexpr PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(test_constexpr PUBLIC -fprofile-arcs -ftest-coverage)
endif()
