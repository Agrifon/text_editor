include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(core_tests core/test_document.cpp)

target_link_libraries(core_tests PRIVATE gtest_main core)

include(GoogleTest)
gtest_discover_tests(core_tests)
