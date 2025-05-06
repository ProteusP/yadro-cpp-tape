file(GLOB SOURCES
    *.cpp
)

add_executable(TapeSorter ${SOURCES})

target_include_directories(TapeSorter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ../third_party)
