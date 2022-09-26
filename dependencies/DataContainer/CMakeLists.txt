message(STATUS "Fetching DataContainer...")

FetchContent_Declare(
        DataContainer
        GIT_REPOSITORY https://github.com/schombert/DataContainer
        GIT_TAG ca3148b5cd938a9aadafa95b1a599516a0eba4ab # 0.2
)

FetchContent_MakeAvailable(DataContainer)

# SIMD LIB
add_library(DataContainer STATIC
    "${datacontainer_SOURCE_DIR}/CommonIncludes/catch.hpp"
    "${datacontainer_SOURCE_DIR}/CommonIncludes/common_types.hpp"
    "${datacontainer_SOURCE_DIR}/CommonIncludes/ve_avx.hpp"
    "${datacontainer_SOURCE_DIR}/CommonIncludes/ve_avx2.hpp"
    "${datacontainer_SOURCE_DIR}/CommonIncludes/ve_sse.hpp"
    "${datacontainer_SOURCE_DIR}/CommonIncludes/ve.hpp")
set_target_properties(DataContainer PROPERTIES LINKER_LANGUAGE CXX)

add_library(dependency_DataContainer INTERFACE)
target_link_libraries(dependency_DataContainer INTERFACE DataContainer)

# CONTAINER GENERATOR
file(GLOB_RECURSE GENERATOR_SOURCE "${datacontainer_SOURCE_DIR}/DataContainerGenerator/*.cpp")

add_executable(GENERATOR ${GENERATOR_SOURCE})
include_directories("${datacontainer_SOURCE_DIR}/DataContainerGenerator/")