message(STATUS "Fetching glfw...")

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 7482de6071d21db77a7236155da44c172a7f6c9e # 3.3.8
)

FetchContent_MakeAvailable(glfw)

add_library(dependency_glfw INTERFACE)
target_link_libraries(dependency_glfw INTERFACE glfw)