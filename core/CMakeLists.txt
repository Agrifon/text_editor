file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/**/*.cpp"
)

add_library(core SHARED ${SOURCES})
target_include_directories(core PUBLIC include)

