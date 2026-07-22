file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/**/*.cpp"
)

add_library(gui SHARED ${SOURCES})
target_include_directories(gui PUBLIC include)
target_link_libraries(gui PUBLIC core)

