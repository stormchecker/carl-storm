# Libraries
add_subdirectory(carl)

# For unit tests.
if(PROJECT_IS_TOP_LEVEL AND CARL_BUILD_TESTS)
    add_subdirectory(tests)

    # For examples.
    add_subdirectory(examples EXCLUDE_FROM_ALL)
endif()
