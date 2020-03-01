cmake_minimum_required(VERSION 3.1.3)

project(absinthe)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wnull-dereference -Wold-style-cast -Wshadow -pedantic-errors -Werror")
endif()

if ( CMAKE_COMPILER_IS_GNUCC )
	if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "6" OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "6")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnull-dereference -Wduplicated-cond")
	endif()
	if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "7" OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "7")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-branches" )
	endif()

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wlogical-op -Wold-style-cast -Wuseless-cast -Wshadow -pedantic-errors -Werror")
endif ( CMAKE_COMPILER_IS_GNUCC )
if ( MSVC )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
endif ( MSVC )

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_COLOR_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 17)

set(TEST_SOURCES
	test/single_char_parser.cpp
	test/string_parser.cpp
	test/int_parser.cpp
	test/uint_parser.cpp
	test/double_parser.cpp
	test/sequence_parser.cpp
	test/repeated_parser.cpp
)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_SOURCE_DIR}/include")
include_directories(${CATCH_INCLUDE_DIR})

enable_testing()
foreach( testsourcefile ${TEST_SOURCES} )
    string( REPLACE "test/" "" testname ${testsourcefile} )
    string( REPLACE ".cpp" "" testname ${testname} )
    add_executable( ${testname} ${testsourcefile} )
    target_link_libraries(${testname} Catch)
	add_test( ${testname} ${testname})
endforeach( testsourcefile ${TEST_SOURCES} )
