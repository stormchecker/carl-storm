if(CARL_EIGEN_SOURCE_DIR)
	set(CARL_EIGEN_DIR ${CARL_EIGEN_SOURCE_DIR})
else()
	set(CARL_EIGEN_DIR ${PROJECT_BINARY_DIR}/resources/Eigen)
	ExternalProject_Add(
			eigen_carl_src
			GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
			# This tag should be set from Storm to coincide with Storm's Eigen version
			GIT_TAG ${CARL_EIGEN_GIT_TAG}
			SOURCE_DIR ${CARL_EIGEN_DIR}
			# First check whether patch was already applied (--reverse --check), otherwise apply patch
			#PATCH_COMMAND git apply ${STORM_3RDPARTY_SOURCE_DIR}/patches/eigen501.patch --reverse --check -q || git apply ${STORM_3RDPARTY_SOURCE_DIR}/patches/eigen501.patch
			UPDATE_COMMAND ""
			CONFIGURE_COMMAND ""
			BUILD_COMMAND ""
			INSTALL_COMMAND ""
			LOG_INSTALL ON
	)
endif()
add_library(eigencarl INTERFACE) # Not imported, we are in control of the sources.
if(NOT CARL_EIGEN_SOURCE_DIR)
	add_dependencies(eigencarl eigen_carl_src)
endif()
# note that we include without Eigen
target_include_directories(eigencarl INTERFACE
		$<BUILD_INTERFACE:${CARL_EIGEN_DIR}>
		$<INSTALL_INTERFACE:${CARL_INCLUDE_INSTALL_DIR}/carl/resources/Eigen>
)
install(TARGETS eigencarl EXPORT carl_Targets)
install(DIRECTORY ${CARL_EIGEN_DIR}/Eigen
		DESTINATION ${CARL_INCLUDE_INSTALL_DIR}/carl/resources/Eigen
)
list(APPEND CARL_TARGETS eigencarl)
