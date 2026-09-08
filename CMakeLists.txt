cmake_minimum_required(VERSION 3.10)
project(sha VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# ========= options ========
option(SHA_BUILD_EXAMPLES "Build the example executables" OFF)

# ========= source files ========
set(LIB_SOURCES
        src/SHA256.cpp
        src/SHA384.cpp
        src/SHA512.cpp
)

# ========= header files ========
set(LIB_HEADERS
        src/SHA256.h
        src/SHA384.h
        src/SHA512.h
)

# ========= created static library ========
add_library(sha_static STATIC ${LIB_SOURCES})
set_target_properties(sha_static PROPERTIES
        OUTPUT_NAME "sha_static"
        EXPORT_NAME "static"
)
target_include_directories(sha_static PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)
add_library(sha::static ALIAS sha_static)

# ========= created shared library ========
add_library(sha_shared SHARED ${LIB_SOURCES})
set_target_properties(sha_shared PROPERTIES
        OUTPUT_NAME "sha"
        EXPORT_NAME "shared"
)
target_include_directories(sha_shared PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)
if(WIN32)
    set_target_properties(sha_shared PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()
add_library(sha::shared ALIAS sha_shared)

# ========= compile examples ========
if (SHA_BUILD_EXAMPLES)
    add_executable(sha-example-static src/example.cpp)
    target_link_libraries(sha-example-static PRIVATE sha::static)

    add_executable(sha-example-shared src/example.cpp)
    target_link_libraries(sha-example-shared PRIVATE sha::shared)
endif()

# ========= install library targets ========
install(TARGETS sha_static sha_shared
        EXPORT SHAExports # Name of the export set
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# ========= install header files ========
install(FILES ${LIB_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# ========= cmake package config destination ========
set(SHA_CMAKE_CONFIG_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SHA")

# ========= install cmake export file ========
install(EXPORT SHAExports
        FILE SHAExports.cmake
        NAMESPACE sha::
        DESTINATION ${SHA_CMAKE_CONFIG_DESTINATION}
)

# ========= generate and install package version file ========
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/SHAConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

# ========= generate package config file ========
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/SHAConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/SHAConfig.cmake"
        INSTALL_DESTINATION ${SHA_CMAKE_CONFIG_DESTINATION}
)

# ========= install package config files ========
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/SHAConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/SHAConfigVersion.cmake"
        DESTINATION ${SHA_CMAKE_CONFIG_DESTINATION}
)
