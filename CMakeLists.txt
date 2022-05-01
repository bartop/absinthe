cmake_minimum_required(VERSION 3.23.0)

project(absinthe VERSION 0.1.0 LANGUAGES CXX) 

find_package(Catch2 REQUIRED)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wnull-dereference -Wold-style-cast -Wshadow -pedantic-errors -Werror")
endif()

if(CMAKE_COMPILER_IS_GNUCC)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "6" OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "6")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnull-dereference -Wduplicated-cond")
    endif()
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "7" OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "7")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-branches")
    endif()

    set(
        CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wlogical-op -Wold-style-cast -Wuseless-cast -Wshadow -pedantic-errors -Werror")
endif(CMAKE_COMPILER_IS_GNUCC)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
endif(MSVC)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)

add_library(absinthe INTERFACE)
target_include_directories(
    absinthe
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/absinthe>
)

set(INCLUDE_FILES
    absinthe.hpp alternative_parser.hpp char_parser.hpp char_set_parser.hpp
    custom_type_parser.hpp difference_parser.hpp double_parser.hpp
    int_parser.hpp omitting_parser.hpp optional_parser.hpp parse.hpp
    parser_error.hpp parse_result.hpp peek_parser.hpp repeated_parser.hpp
    sequence_parser.hpp single_char_parser.hpp specific_char_parsers.hpp
    string_parser.hpp traits.hpp uint_parser.hpp
)

set(INCLUDE_PATHS "")

foreach(FILE_NAME ${INCLUDE_FILES})
    set(INCLUDE_PATHS
	${INCLUDE_PATHS}
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/absinthe/${FILE_NAME}>"
        "$<INSTALL_INTERFACE:include/absinthe/absinthe/${FILE_NAME}>"
    )
endforeach()

target_sources(
    absinthe PUBLIC
    FILE_SET HEADERS TYPE HEADERS
    BASE_DIRS
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include/absinthe>
    FILES ${INCLUDE_PATHS}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/absintheConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/absintheConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/absintheConfig.cmake"
    INSTALL_DESTINATION lib/cmake/absinthe
)

install(TARGETS absinthe
    EXPORT absintheTargets
    FILE_SET HEADERS
    DESTINATION include/absinthe
)

install(EXPORT absintheTargets DESTINATION lib/cmake/absinthe)
install(FILES
    "${PROJECT_BINARY_DIR}/absintheConfig.cmake"
    "${PROJECT_BINARY_DIR}/absintheConfigVersion.cmake"
    DESTINATION lib/cmake/absinthe
)

set(TEST_SOURCES
    test/single_char_parser.cpp
    test/string_parser.cpp
    test/int_parser.cpp
    test/uint_parser.cpp
    test/double_parser.cpp
    test/sequence_parser.cpp
    test/repeated_parser.cpp
    test/alternative_parser.cpp
    test/difference_parser.cpp
    test/peek_parser.cpp
    test/custom_type_parser.cpp
    test/omitting_parser.cpp
    test/optional_parser.cpp
    test/char_set_parser.cpp
    test/parse.cpp
    test/specific_char_parsers.cpp
)

enable_testing()
add_executable(unit_tests ${TEST_SOURCES} test/main.cpp)

target_link_libraries(unit_tests PRIVATE absinthe Catch2::Catch2)
add_test(NAME unit_tests COMMAND unit_tests)
include(CPack)
