include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(core_tests core/test_document.cpp)
target_link_libraries(core_tests PRIVATE gtest_main core)

if(WIN32)
    add_custom_command(TARGET core_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:core>
            $<TARGET_FILE_DIR:core_tests>
        COMMENT "Copying core.dll to test executable directory"
    )
endif()
    
set_target_properties(core_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${PLATFORM}/tests
)

include(GoogleTest)
gtest_discover_tests(core_tests)
