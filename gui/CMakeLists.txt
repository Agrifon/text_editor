file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/**/*.cpp"
)

file(GLOB_RECURSE HEADERS "include/gui/*.h") #for automoc

add_library(gui SHARED ${SOURCES} ${HEADERS})
target_include_directories(gui PUBLIC include)
target_link_libraries(gui PUBLIC Qt6::Widgets core)

