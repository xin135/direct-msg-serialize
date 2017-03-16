CMAKE_MINIMUM_REQUIRED (VERSION 2.8.6)

PROJECT (dms)

SET (prefix ${CMAKE_INSTALL_PREFIX})
SET (exec_prefix "\${prefix}")
SET (libdir "\${exec_prefix}/lib")
SET (includedir "\${prefix}/include")
SET (GNUCXX_STD_SUPPORT_VERSION "4.3")

OPTION (MSGPACK_32BIT "32bit compile" OFF)

IF (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
  IF ((CMAKE_CXX_COMPILER_VERSION VERSION_GREATER ${GNUCXX_STD_SUPPORT_VERSION}) OR
    (CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL   ${GNUCXX_STD_SUPPORT_VERSION}))
	SET (CMAKE_CXX_FLAGS "-std=c++98 ${CMAKE_CXX_FLAGS}")
  ENDIF ()
ELSEIF (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
  SET (CMAKE_CXX_FLAGS "-std=c++98 ${CMAKE_CXX_FLAGS}")
ELSEIF (MSVC)
  IF (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 18)
    SET (CMAKE_CXX_FLAGS "-DMSGPACK_USE_CPP03 ${CMAKE_CXX_FLAGS}")
  ENDIF ()
ENDIF ()

OPTION (DMS_BUILD_EXAMPLES "Build dms examples." ON)

INCLUDE (Files.cmake)

INCLUDE_DIRECTORIES ( 
    ./
    include/
	src/
	third_party/
)           

ADD_LIBRARY (libdms SHARED
	${dms_SOURCES}
	${dms_HEADERS}
)
SET_TARGET_PROPERTIES(
	libdms
	PROPERTIES
	COMPILE_DEFINITIONS DMS_SDK_EXPORT
)
			
ADD_LIBRARY (libdms-static STATIC
	${dms_SOURCES}
	${dms_HEADERS}
)
SET_TARGET_PROPERTIES(
	libdms-static
	PROPERTIES
	COMPILE_DEFINITIONS DMS_STATIC
)

IF (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang" OR ${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
    SET_PROPERTY (TARGET libdms APPEND_STRING PROPERTY COMPILE_FLAGS "-Wall -Wextra -Werror -g -O3 -DPIC")
    SET_PROPERTY (TARGET libdms-static APPEND_STRING PROPERTY COMPILE_FLAGS "-Wall -Wextra -Werror -g -O3" )
ENDIF ()

IF (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
    SET_PROPERTY (TARGET libdms APPEND_STRING PROPERTY COMPILE_FLAGS " -Wno-mismatched-tags")
    SET_PROPERTY (TARGET libdms-static APPEND_STRING PROPERTY COMPILE_FLAGS " -Wno-mismatched-tags")
ENDIF ()

IF (MSVC)
    IF (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        STRING(REGEX REPLACE "/W[0-4]" "/W3 /WX" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    ELSE ()
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /WX")
    ENDIF ()
ENDIF ()

IF (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC90" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC10")
    SET_SOURCE_FILES_PROPERTIES(${dms_SOURCES} PROPERTIES LANGUAGE CXX)
ENDIF()

IF (NOT DEFINED CMAKE_INSTALL_BINDIR)
    SET(CMAKE_INSTALL_BINDIR bin)
ENDIF ()

IF (NOT DEFINED CMAKE_INSTALL_LIBDIR)
    SET(CMAKE_INSTALL_LIBDIR lib)
ENDIF ()

IF (DMS_BUILD_EXAMPLES)
    ADD_SUBDIRECTORY (examples)
ENDIF ()

SET (LIBDMS_INSTALLTARGETS libdms libdms-static)

INSTALL (TARGETS ${LIBDMS_INSTALLTARGETS} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
                                          LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                                          ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               