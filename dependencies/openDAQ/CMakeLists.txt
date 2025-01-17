include(FetchContent)

set(Boost_USE_STATIC_LIBS				OFF)
set(DAQMODULES_OPENDAQ_CLIENT_MODULE	OFF)
set(DAQMODULES_OPENDAQ_SERVER_MODULE	${COMPILE_REFERENCE_APPLICATION})
set(DAQMODULES_EMPTY_MODULE				OFF)
set(DAQMODULES_REF_FB_MODULE			OFF)
set(DAQMODULES_REF_DEVICE_MODULE		${COMPILE_REFERENCE_APPLICATION})
set(OPENDAQ_ENABLE_TESTS				OFF)
set(OPENDAQ_ENABLE_NATIVE_STREAMING     OFF)
set(OPENDAQ_ENABLE_WEBSOCKET_STREAMING  OFF)
set(OPENDAQ_ENABLE_OPCUA                ${COMPILE_REFERENCE_APPLICATION})

if(NOT IGNORE_INSTALLED_SDK)
    find_package(openDAQ QUIET GLOBAL)
endif()

if(openDAQ_FOUND)

	include("${openDAQ_DIR}/../../../share/cmake/openDAQUtils.cmake")

else()

	if(NOT IGNORE_INSTALLED_SDK)
        message(WARNING
            "IGNORE_INSTALLED_SDK is not set, but the openDAQ SDK was not "
            "found. The openDAQ SDK will be downloaded and built internally. "
            "Set IGNORE_INSTALLED_SDK=ON to suppress this warning.")
    endif()

	FetchContent_Declare(openDAQ-SDK
		GIT_REPOSITORY		"${OPENDAQ_REPO_PREFIX}/openDAQ.git"
		GIT_PROGRESS		TRUE
		GIT_TAG				"11e2d176b86686dcd4b346e482e665534b6d7d0e"
		SOURCE_DIR			${CMAKE_CURRENT_SOURCE_DIR}/src
	)

	FetchContent_MakeAvailable(openDAQ-SDK)

endif()
