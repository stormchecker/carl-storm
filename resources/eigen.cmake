include(FetchContent)
# Uses the same FetchContent name as Storm: if carl is built within Storm, Storm's Eigen checkout is reused.
FetchContent_Declare(
		eigen
		# GitHub mirror of Eigen, used for availability reasons.
		GIT_REPOSITORY https://github.com/eigen-mirror/eigen.git
		GIT_TAG ${CARL_EIGEN_GIT_TAG}
		SOURCE_DIR ${PROJECT_BINARY_DIR}/resources/Eigen
		# Eigen ships its own CMakeLists.txt, which we do not want to process.
		# Pointing SOURCE_SUBDIR at a subdirectory with no CMakeLists.txt makes FetchContent_MakeAvailable() populate
		# the source without calling add_subdirectory() on it.
		SOURCE_SUBDIR do-not-add-as-subdirectory
)
FetchContent_MakeAvailable(eigen)
add_library(eigencarl INTERFACE) # Not imported, we are in control of the sources.
# note that we include without Eigen
target_include_directories(eigencarl INTERFACE
		$<BUILD_INTERFACE:${eigen_SOURCE_DIR}>
		$<INSTALL_INTERFACE:${CARL_INCLUDE_INSTALL_DIR}/carl/resources/Eigen>
)
install(TARGETS eigencarl EXPORT carl_Targets)
install(DIRECTORY ${eigen_SOURCE_DIR}/Eigen
		DESTINATION ${CARL_INCLUDE_INSTALL_DIR}/carl/resources/Eigen
)
list(APPEND CARL_TARGETS eigencarl)
