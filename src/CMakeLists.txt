# Libraries
add_subdirectory(carl)

# For unit tests.
if(PROJECT_IS_TOP_LEVEL AND CARL_BUILD_TESTS)
    add_subdirectory(tests)
endif()
