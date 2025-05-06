file(GLOB TEST_SOURCES *.cpp)

set(SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/FileTape.cpp
    ${PROJECT_SOURCE_DIR}/src/Config.cpp
    ${PROJECT_SOURCE_DIR}/src/TapeSorter.cpp
)

add_executable(UnitTests ${TEST_SOURCES} ${SRC_FILES})

target_include_directories(UnitTests PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/third_party
)

target_link_libraries(UnitTests
    gtest
    gtest_main
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(UnitTests)
