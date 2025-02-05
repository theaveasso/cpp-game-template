project(Extlibs CXX)

include(FetchContent)

set(EXTLIBS)

FetchContent_Declare(
    SDL
    GIT_REPOSITORY git@github.com:libsdl-org/SDL.git
    GIT_TAG main
)
FetchContent_Declare(
    SDL_image
    GIT_REPOSITORY git@github.com:libsdl-org/SDL_image.git
    GIT_TAG main
)
FetchContent_Declare(
    ImGUI
    GIT_REPOSITORY git@github.com:ocornut/imgui.git
    GIT_TAG docking
)

FetchContent_MakeAvailable(ImGUI SDL SDL_image)

add_library(IMGUI STATIC)
add_library(${PROJECT_NAME} INTERFACE)

target_sources(IMGUI PRIVATE
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)
target_include_directories(IMGUI PUBLIC ${imgui_SOURCE_DIR})
target_include_directories(IMGUI PUBLIC ${SDL3_SOURCE_DIR}/include)
target_include_directories(IMGUI PUBLIC ${imgui_SOURCE_DIR}/backends)

list(APPEND EXTLIBS SDL3::SDL3 SDL3_image::SDL3_image IMGUI)

target_link_libraries(${PROJECT_NAME} INTERFACE ${EXTLIBS})
