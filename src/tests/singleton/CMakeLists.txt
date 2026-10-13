# Probe library: a downstream-like shared library with hidden visibility that calls getInstance() of all singletons.
add_library(carl_singleton_probe SHARED SingletonProbe.cpp)
target_link_libraries(carl_singleton_probe PRIVATE lib_carl carl_storm_compiler_warnings)
set_target_properties(carl_singleton_probe PROPERTIES
	CXX_VISIBILITY_PRESET hidden
	VISIBILITY_INLINES_HIDDEN ON
	POSITION_INDEPENDENT_CODE ON)

add_executable(runSingletonTests Test_SingletonUniqueness.cpp)
target_link_libraries(runSingletonTests TestCommon carl_singleton_probe)
add_test(NAME singleton COMMAND runSingletonTests)
add_dependencies(all-tests runSingletonTests)
