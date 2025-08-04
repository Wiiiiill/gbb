cmake_minimum_required(VERSION 2.8)
message(STATUS "Build GB BASIC for Linux...")

# Projects.
project(gbbasic)

# Architectures.
set(GBBASIC_SPEC no)
if ("${arch}" STREQUAL "x64")
  set(GBBASIC_SPEC 64)
endif ()
if ("${arch}" STREQUAL "x86")
  set(GBBASIC_SPEC 86)
endif ()
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(STATUS "Host arch: x64")
  set(GBBASIC_IS_X64 TRUE)
  set(GBBASIC_ARCH 64)
  set(GBBASIC_BITS 64)
else ()
  message(STATUS "Host arch: x86")
  set(GBBASIC_IS_X64 FALSE)
  set(GBBASIC_ARCH 86)
  set(GBBASIC_BITS 32)
endif ()
if (${GBBASIC_SPEC} STREQUAL no)
  message(STATUS "Specified arch: no")
else ()
  message(STATUS "Specified arch: " ${GBBASIC_SPEC})
  if (${GBBASIC_SPEC} STREQUAL 64)
    if (NOT ${GBBASIC_IS_X64})
      set(GBBASIC_IS_X64 TRUE)
      set(GBBASIC_ARCH 64)
      set(GBBASIC_BITS 64)
      set(CMAKE_C_FLAGS "-m64")
      set(CMAKE_CXX_FLAGS "-m64")
    endif ()
  else ()
    if (${GBBASIC_IS_X64})
      set(GBBASIC_IS_X64 FALSE)
      set(GBBASIC_ARCH 86)
      set(GBBASIC_BITS 32)
      set(CMAKE_C_FLAGS "-m32")
      set(CMAKE_CXX_FLAGS "-m32")
    endif ()
  endif ()
endif ()
message(STATUS "Is x64: " ${GBBASIC_IS_X64})
set(GBBASIC_TEMP ./)
set(${arch} "")

# Profiles.
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif ()
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
if (${CMAKE_BUILD_TYPE} STREQUAL Release)
  list(
    APPEND GBBASIC_DEF
    NDEBUG
  )
else ()
  list(
    APPEND GBBASIC_DEF
    _DEBUG
  )
endif ()

# Requirements.
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Sources.
list(
  APPEND GBBASIC_LIB_B64
  "../lib/b64/buffer.c"
  "../lib/b64/decode.c"
  "../lib/b64/encode.c"
)
list(
  APPEND GBBASIC_LIB_BINJGB
  "../lib/binjgb/src/common.c"
  "../lib/binjgb/src/emulator-debug.c"
  "../lib/binjgb/src/joypad.c"
  "../lib/binjgb/src/memory.c"
  "../lib/binjgb/src/options.c"
  "../lib/binjgb/src/rewind.c"
)
list(
  APPEND GBBASIC_LIB_CLIP
  "../lib/clip/clip.cpp"
  "../lib/clip/clip_x11.cpp"
  "../lib/clip/image_.cpp"
)
list(
  APPEND GBBASIC_LIB_IMGUI
  "../lib/imgui/imgui.cpp"
  "../lib/imgui/imgui_demo.cpp"
  "../lib/imgui/imgui_draw.cpp"
  "../lib/imgui/imgui_tables.cpp"
  "../lib/imgui/imgui_widgets.cpp"
)
list(
  APPEND GBBASIC_LIB_IMGUI_CODE_EDITOR
  "../lib/imgui_code_editor/imgui_code_editor.cpp"
)
list(
  APPEND GBBASIC_LIB_IMGUI_SDL
  "../lib/imgui_sdl/imgui_sdl.cpp"
)
list(
  APPEND GBBASIC_LIB_JO_GIF
  "../lib/jo_gif/jo_gif.cpp"
)
list(
  APPEND GBBASIC_LIB_LZ4
  "../lib/lz4/lib/lz4.c"
  "../lib/lz4/lib/lz4frame.c"
  "../lib/lz4/lib/lz4hc.c"
  "../lib/lz4/lib/xxhash.c"
)
list(
  APPEND GBBASIC_LIB_MD4C
  "../lib/md4c/src/md4c.c"
)
list(
  APPEND GBBASIC_LIB_CIVETWEB
  "../lib/civetweb/src/civetweb.c"
)
list(
  APPEND GBBASIC_LIB_MPC
  "../lib/mpc/mpc.c"
)
list(
  APPEND GBBASIC_LIB_PORTABLE_FILE_DIALOGS
  "../lib/portable_file_dialogs/portable-file-dialogs.cpp"
)
list(
  APPEND GBBASIC_LIB_PROMISE
  "../lib/promise_cpp/src/promise.cpp"
)
list(
  APPEND GBBASIC_LIB_ZLIB
  "../lib/zlib/contrib/minizip/ioapi.c"
  "../lib/zlib/contrib/minizip/mztools.c"
  "../lib/zlib/contrib/minizip/unzip.c"
  "../lib/zlib/contrib/minizip/zip.c"
  "../lib/zlib/adler32.c"
  "../lib/zlib/compress.c"
  "../lib/zlib/crc32.c"
  "../lib/zlib/deflate.c"
  "../lib/zlib/gzclose.c"
  "../lib/zlib/gzlib.c"
  "../lib/zlib/gzread.c"
  "../lib/zlib/gzwrite.c"
  "../lib/zlib/infback.c"
  "../lib/zlib/inffast.c"
  "../lib/zlib/inflate.c"
  "../lib/zlib/inftrees.c"
  "../lib/zlib/trees.c"
  "../lib/zlib/uncompr.c"
  "../lib/zlib/zutil.c"
)
list(
  APPEND GBBASIC_SRC_APP
  "../src/app/device_binjgb.cpp"
  "../src/app/command.cpp"
  "../src/app/commands_actor.cpp"
  "../src/app/commands_font.cpp"
  "../src/app/commands_grouped.cpp"
  "../src/app/commands_layered.cpp"
  "../src/app/commands_map.cpp"
  "../src/app/commands_music.cpp"
  "../src/app/commands_paintable.cpp"
  "../src/app/commands_paintable2d.cpp"
  "../src/app/commands_scene.cpp"
  "../src/app/commands_sfx.cpp"
  "../src/app/commands_tiles.cpp"
  "../src/app/editing.cpp"
  "../src/app/editor.cpp"
  "../src/app/editor_actor.cpp"
  "../src/app/editor_arbitrary.cpp"
  "../src/app/editor_code.cpp"
  "../src/app/editor_code_binding.cpp"
  "../src/app/editor_code_language_definition.cpp"
  "../src/app/editor_console.cpp"
  "../src/app/editor_font.cpp"
  "../src/app/editor_map.cpp"
  "../src/app/editor_music.cpp"
  "../src/app/editor_palette.cpp"
  "../src/app/editor_properties.cpp"
  "../src/app/editor_ref_resolver.cpp"
  "../src/app/editor_scene.cpp"
  "../src/app/editor_search_result.cpp"
  "../src/app/editor_sfx.cpp"
  "../src/app/editor_tiles.cpp"
  "../src/app/resource/inline_resource.cpp"
  "../src/app/activities.cpp"
  "../src/app/application.cpp"
  "../src/app/device.cpp"
  "../src/app/document.cpp"
  "../src/app/emulator.cpp"
  "../src/app/exporter.cpp"
  "../src/app/operations.cpp"
  "../src/app/project.cpp"
  "../src/app/settings.cpp"
  "../src/app/theme.cpp"
  "../src/app/widgets.cpp"
  "../src/app/workspace.cpp"
)
list(
  APPEND GBBASIC_SRC_COMPILER
  "../src/compiler/codepoint.cpp"
  "../src/compiler/compiler.cpp"
  "../src/compiler/kernel.cpp"
  "../src/compiler/pipeline.cpp"
  "../src/compiler/static_analyzer.cpp"
)
list(
  APPEND GBBASIC_SRC_UTILS
  "../src/utils/archive_zip.cpp"
  "../src/utils/actor.cpp"
  "../src/utils/assets.cpp"
  "../src/utils/font.cpp"
  "../src/utils/image.cpp"
  "../src/utils/indexed.cpp"
  "../src/utils/map.cpp"
  "../src/utils/music.cpp"
  "../src/utils/scene.cpp"
  "../src/utils/sfx.cpp"
  "../src/utils/trigger.cpp"
  "../src/utils/platform_linux.cpp"
  "../src/utils/web_civetweb.cpp"
  "../src/utils/archive.cpp"
  "../src/utils/bytes.cpp"
  "../src/utils/cloneable.cpp"
  "../src/utils/colour.cpp"
  "../src/utils/datetime.cpp"
  "../src/utils/dispatchable.cpp"
  "../src/utils/editable.cpp"
  "../src/utils/either.cpp"
  "../src/utils/encoding.cpp"
  "../src/utils/entry.cpp"
  "../src/utils/file_handle.cpp"
  "../src/utils/file_sandbox.cpp"
  "../src/utils/filesystem.cpp"
  "../src/utils/generic.cpp"
  "../src/utils/hacks.cpp"
  "../src/utils/input.cpp"
  "../src/utils/json.cpp"
  "../src/utils/localization.cpp"
  "../src/utils/marker.cpp"
  "../src/utils/mathematics.cpp"
  "../src/utils/matrice.cpp"
  "../src/utils/object.cpp"
  "../src/utils/parsers.cpp"
  "../src/utils/platform.cpp"
  "../src/utils/plus.cpp"
  "../src/utils/recorder.cpp"
  "../src/utils/renderer.cpp"
  "../src/utils/rom_inspector.cpp"
  "../src/utils/shapes.cpp"
  "../src/utils/stream.cpp"
  "../src/utils/text.cpp"
  "../src/utils/texture.cpp"
  "../src/utils/updatable.cpp"
  "../src/utils/web.cpp"
  "../src/utils/window.cpp"
  "../src/utils/work_queue.cpp"
)
add_executable(
  gbbasic
  ${GBBASIC_LIB_B64}
  ${GBBASIC_LIB_BINJGB}
  # ${GBBASIC_LIB_CLIP}
  ${GBBASIC_LIB_IMGUI}
  ${GBBASIC_LIB_IMGUI_CODE_EDITOR}
  ${GBBASIC_LIB_IMGUI_SDL}
  ${GBBASIC_LIB_JO_GIF}
  ${GBBASIC_LIB_LZ4}
  ${GBBASIC_LIB_MD4C}
  ${GBBASIC_LIB_CIVETWEB}
  ${GBBASIC_LIB_MPC}
  ${GBBASIC_LIB_PORTABLE_FILE_DIALOGS}
  ${GBBASIC_LIB_PROMISE}
  ${GBBASIC_LIB_ZLIB}
  ${GBBASIC_SRC_APP}
  ${GBBASIC_SRC_COMPILER}
  ${GBBASIC_SRC_UTILS}
  "../src/main.cpp"
)
list(
  APPEND GBBASIC_INC
  "../lib/civetweb/include"
  "../lib/civetweb/src"
  "../lib/imgui"
  "../lib/rapidfuzz_cpp"
  "../lib/sdl/include"
  "../lib/zlib"
)
target_include_directories(gbbasic PRIVATE ${GBBASIC_INC})

# Compiling.
list(
  APPEND GBBASIC_DEF
  NO_SSL
  CLIP_ENABLE_IMAGE
)
target_compile_definitions(gbbasic PRIVATE ${GBBASIC_DEF})

# Flags.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format-security -Wno-unused-result")
set_source_files_properties("../src/utils/file_sandbox.cpp" PROPERTIES COMPILE_FLAGS -Wno-deprecated-declarations)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# Linkage.
list(
  APPEND GBBASIC_LIB
  m
  pthread
  rt
  stdc++fs
)
target_link_libraries(gbbasic ${GBBASIC_LIB})

# OpenGL.
target_link_libraries(gbbasic ${OPENGL_LIBRARIES})

# GTK.
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})
target_link_libraries(gbbasic ${GTK3_LIBRARIES})

# SDL.
include_directories("../lib/sdl/lib/x${GBBASIC_ARCH}")
add_library(libsdl SHARED IMPORTED)
set_target_properties(libsdl PROPERTIES IMPORTED_LOCATION "./libSDL2-2.0.so.0")
target_link_libraries(gbbasic libsdl)
add_library(libsndio SHARED IMPORTED)
set_target_properties(libsndio PROPERTIES IMPORTED_LOCATION "./libsndio.so.6.1")
target_link_libraries(gbbasic libsndio)

# Prev event.
add_custom_target(
  gbbasic_prev_sdl
  COMMAND cp "../lib/sdl/lib/x${GBBASIC_ARCH}/libSDL2.a" ${GBBASIC_TEMP}
  COMMAND cp "../lib/sdl/lib/x${GBBASIC_ARCH}/libSDL2-2.0.so.0" ${GBBASIC_TEMP}
  COMMAND cp "../lib/sdl/lib/x${GBBASIC_ARCH}/libsndio.so.6.1" ${GBBASIC_TEMP}
)
add_dependencies(gbbasic gbbasic_prev_sdl)

# Post event.
add_custom_command(
  TARGET gbbasic POST_BUILD
  COMMAND file "${GBBASIC_TEMP}gbbasic"
  COMMAND file "${GBBASIC_TEMP}libSDL2-2.0.so.0"
  COMMAND cp "${GBBASIC_TEMP}gbbasic" "../gbbasic/x${GBBASIC_ARCH}_release/"
  COMMAND cp "${GBBASIC_TEMP}libSDL2-2.0.so.0" "../gbbasic/x${GBBASIC_ARCH}_release/"
  COMMAND cp "${GBBASIC_TEMP}libsndio.so.6.1" "../gbbasic/x${GBBASIC_ARCH}_release/"
)
