# Project name and version
NAME=Overcomplicated-Snake
VERSION=v1.0.0
EXEC=${NAME}-${VERSION}

# Compiler
C_COMPILER=clang
CPP_COMPILER=clang++
LINTER=clang-tidy

# Common Options
OPTIONS=-Wall
RELEASE_OPTIONS=${OPTIONS} -O3
DEBUG_OPTIONS=${OPTIONS} -Og -g3
# Compiler options
C_OPTIONS=-I /usr/include/ -std=c17
C_RELEASE_OPTIONS=${RELEASE_OPTIONS} ${C_OPTIONS}
C_DEBUG_OPTIONS=${DEBUG_OPTIONS} ${C_OPTIONS}
CPP_OPTIONS=-I /usr/include/ -std=c++20
CPP_RELEASE_OPTIONS=${RELEASE_OPTIONS} ${CPP_OPTIONS}
CPP_DEBUG_OPTIONS=${DEBUG_OPTIONS} ${CPP_OPTIONS} -D SNAKE_DEBUG_INPUT=false
# Linker options
LN_OPTIONS=-L /usr/lib/ -l glfw -l wayland-client -l X11 -l Xrandr -l vulkan -l GL
LN_RELEASE_OPTIONS=${RELEASE_OPTIONS} ${LN_OPTIONS} -s
LN_DEBUG_OPTIONS=${DEBUG_OPTIONS} ${LN_OPTIONS}

# Wayland options
WAYLAND_SCANNER=wayland-scanner

WAYLAND_PROTOCOLS_DIR=$(shell pkg-config wayland-protocols --variable=pkgdatadir)
WAYLAND_CORE_PROTOCOL=$(shell pkg-config wayland-client --variable=pkgdatadir)/wayland.xml
XDG_SHELL_PROTOCOL=${WAYLAND_PROTOCOLS_DIR}/stable/xdg-shell/xdg-shell.xml
XDG_TOPLEVEL_ICON_PROTOCOL=${WAYLAND_PROTOCOLS_DIR}/staging/xdg-toplevel-icon/xdg-toplevel-icon-v1.xml

WAYLAND_HEADERS=lib/wayland.h lib/xdg-shell.h lib/xdg-toplevel-icon.h
WAYLAND_LIBS=build/wayland.o build/xdg-shell.o build/xdg-toplevel-icon.o


# Build all executables
build: buildRelease buildDebug
# Build all release executables
buildRelease: out/${EXEC}-glfw-vulkan out/${EXEC}-glfw-gl out/${EXEC}-x11-vulkan out/${EXEC}-x11-gl out/${EXEC}-dummy-terminal
# Build all debug executables
buildDebug: out/${EXEC}-glfw-vulkan-debug out/${EXEC}-glfw-gl-debug out/${EXEC}-x11-vulkan-debug out/${EXEC}-x11-gl-debug out/${EXEC}-dummy-terminal-debug


# Main executable (glfw & vulkan variant)
out/${EXEC}-glfw-vulkan: build/main.o build/game.o build/window-glfw.o build/windowevents.o build/keyboard-glfw.o build/renderer-vulkan.o
	@ mkdir -p out/
	${CPP_COMPILER} build/main.o build/game.o build/window-glfw.o build/windowevents.o build/keyboard-glfw.o build/renderer-vulkan.o -o out/${EXEC}-glfw-vulkan ${LN_RELEASE_OPTIONS}
out/${EXEC}-glfw-vulkan-debug: build/main-debug.o build/game-debug.o build/window-glfw-debug.o build/windowevents-debug.o build/keyboard-glfw-debug.o build/renderer-vulkan-debug.o
	@ mkdir -p out/
	${CPP_COMPILER} build/main-debug.o build/game-debug.o build/window-glfw-debug.o build/windowevents-debug.o build/keyboard-glfw-debug.o build/renderer-vulkan-debug.o -o out/${EXEC}-glfw-vulkan-debug ${LN_DEBUG_OPTIONS}

# Main executable (wayland & vulkan variant)
out/${EXEC}-wayland-vulkan: build/main.o build/game.o build/window-wayland.o build/windowevents.o build/keyboard-wayland.o ${WAYLAND_LIBS} build/renderer-vulkan.o
	@ mkdir -p out/
	${CPP_COMPILER} build/main.o build/game.o build/window-wayland.o build/windowevents.o build/keyboard-wayland.o build/renderer-vulkan.o ${WAYLAND_LIBS} -o out/${EXEC}-wayland-vulkan ${LN_RELEASE_OPTIONS}
out/${EXEC}-wayland-vulkan-debug: build/main-debug.o build/game-debug.o build/window-wayland-debug.o build/windowevents-debug.o build/keyboard-wayland-debug.o build/renderer-vulkan-debug.o ${WAYLAND_LIBS}
	@ mkdir -p out/
	${CPP_COMPILER} build/main-debug.o build/game-debug.o build/window-wayland-debug.o build/windowevents-debug.o build/keyboard-wayland-debug.o build/renderer-vulkan-debug.o ${WAYLAND_LIBS} -o out/${EXEC}-wayland-vulkan-debug ${LN_DEBUG_OPTIONS}

# Main executable (x11 & vulkan variant)
out/${EXEC}-x11-vulkan: build/main.o build/game.o build/window-x11.o build/windowevents.o build/keyboard-x11.o build/renderer-vulkan.o
	@ mkdir -p out/
	${CPP_COMPILER} build/main.o build/game.o build/window-x11.o build/windowevents.o build/keyboard-x11.o build/renderer-vulkan.o -o out/${EXEC}-x11-vulkan ${LN_RELEASE_OPTIONS}
out/${EXEC}-x11-vulkan-debug: build/main-debug.o build/game-debug.o build/window-x11-debug.o build/windowevents-debug.o build/keyboard-x11-debug.o build/renderer-vulkan-debug.o
	@ mkdir -p out/
	${CPP_COMPILER} build/main-debug.o build/game-debug.o build/window-x11-debug.o build/windowevents-debug.o build/keyboard-x11-debug.o build/renderer-vulkan-debug.o -o out/${EXEC}-x11-vulkan-debug ${LN_DEBUG_OPTIONS}

# Main executable (glfw & gl variant)
out/${EXEC}-glfw-gl: build/main.o build/game.o build/window-glfw.o build/windowevents.o build/keyboard-glfw.o build/renderer-gl.o
	@ mkdir -p out/
	${CPP_COMPILER} build/main.o build/game.o build/window-glfw.o build/windowevents.o build/keyboard-glfw.o build/renderer-gl.o -o out/${EXEC}-glfw-gl ${LN_RELEASE_OPTIONS}
out/${EXEC}-glfw-gl-debug: build/main-debug.o build/game-debug.o build/window-glfw-debug.o build/windowevents-debug.o build/keyboard-glfw-debug.o build/renderer-gl-debug.o
	@ mkdir -p out/
	${CPP_COMPILER} build/main-debug.o build/game-debug.o build/window-glfw-debug.o build/windowevents-debug.o build/keyboard-glfw-debug.o build/renderer-gl-debug.o -o out/${EXEC}-glfw-gl-debug ${LN_DEBUG_OPTIONS}

# Main executable (wayland & gl variant)
out/${EXEC}-wayland-gl: build/main.o build/game.o build/window-wayland.o build/windowevents.o build/keyboard-wayland.o build/renderer-gl.o ${WAYLAND_LIBS}
	@ mkdir -p out/
	${CPP_COMPILER} build/main.o build/game.o build/window-wayland.o build/windowevents.o build/keyboard-wayland.o build/renderer-gl.o ${WAYLAND_LIBS} -o out/${EXEC}-wayland-gl ${LN_RELEASE_OPTIONS}
out/${EXEC}-wayland-gl-debug: build/main-debug.o build/game-debug.o build/window-wayland-debug.o build/windowevents-debug.o build/keyboard-wayland-debug.o build/renderer-gl-debug.o ${WAYLAND_LIBS}
	@ mkdir -p out/
	${CPP_COMPILER} build/main-debug.o build/game-debug.o build/window-wayland-debug.o build/windowevents-debug.o build/keyboard-wayland-debug.o build/renderer-gl-debug.o ${WAYLAND_LIBS} -o out/${EXEC}-wayland-gl-debug ${LN_DEBUG_OPTIONS}

# Main executable (x11 & gl variant)
out/${EXEC}-x11-gl: build/main.o build/game.o build/window-x11.o build/windowevents.o build/keyboard-x11.o build/renderer-gl.o
	@ mkdir -p out/
	${CPP_COMPILER} build/main.o build/game.o build/window-x11.o build/windowevents.o build/keyboard-x11.o build/renderer-gl.o -o out/${EXEC}-x11-gl ${LN_RELEASE_OPTIONS}
out/${EXEC}-x11-gl-debug: build/main-debug.o build/game-debug.o build/window-x11-debug.o build/windowevents-debug.o build/keyboard-x11-debug.o build/renderer-gl-debug.o
	@ mkdir -p out/
	${CPP_COMPILER} build/main-debug.o build/game-debug.o build/window-x11-debug.o build/windowevents-debug.o build/keyboard-x11-debug.o build/renderer-gl-debug.o -o out/${EXEC}-x11-gl-debug ${LN_DEBUG_OPTIONS}

# Main executable (dummy & terminal variant)
out/${EXEC}-dummy-terminal: build/main.o build/game.o build/window-dummy.o build/windowevents.o build/keyboard-dummy.o build/renderer-terminal.o
	@ mkdir -p out/
	${CPP_COMPILER} build/main.o build/game.o build/window-dummy.o build/windowevents.o build/keyboard-dummy.o build/renderer-terminal.o -o out/${EXEC}-dummy-terminal ${LN_RELEASE_OPTIONS}
out/${EXEC}-dummy-terminal-debug: build/main-debug.o build/game-debug.o build/window-dummy-debug.o build/windowevents-debug.o build/keyboard-dummy-debug.o build/renderer-terminal-debug.o
	@ mkdir -p out/
	${CPP_COMPILER} build/main-debug.o build/game-debug.o build/window-dummy-debug.o build/windowevents-debug.o build/keyboard-dummy-debug.o build/renderer-terminal-debug.o -o out/${EXEC}-dummy-terminal-debug ${LN_DEBUG_OPTIONS}


# main.cpp
build/main.o: src/main.cpp src/game.hpp src/window.hpp src/windowevents.hpp src/keyboard.hpp src/uuid.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/main.cpp -o build/main.o ${CPP_RELEASE_OPTIONS}
build/main-debug.o: src/main.cpp src/game.hpp src/window.hpp src/windowevents.hpp src/keyboard.hpp src/uuid.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/main.cpp -o build/main-debug.o ${CPP_DEBUG_OPTIONS}

# game.cpp
build/game.o: src/game.cpp src/game.hpp src/windowevents.hpp src/keyboard.hpp src/uuid.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/game.cpp -o build/game.o ${CPP_RELEASE_OPTIONS}
build/game-debug.o: src/game.cpp src/game.hpp src/windowevents.hpp src/keyboard.hpp src/uuid.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/game.cpp -o build/game-debug.o ${CPP_DEBUG_OPTIONS}

# window.cpp (glfw variant)
build/window-glfw.o: src/window-glfw.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp src/uuid.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/window-glfw.cpp -o build/window-glfw.o ${CPP_RELEASE_OPTIONS}
build/window-glfw-debug.o: src/window-glfw.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp src/uuid.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/window-glfw.cpp -o build/window-glfw-debug.o ${CPP_DEBUG_OPTIONS}

# window.cpp (wayland variant)
build/window-wayland.o: src/window-wayland.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp src/uuid.hpp ${WAYLAND_HEADERS}
	@ mkdir -p build/
	${CPP_COMPILER} -c src/window-wayland.cpp -o build/window-wayland.o ${CPP_RELEASE_OPTIONS}
build/window-wayland-debug.o: src/window-wayland.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp src/uuid.hpp ${WAYLAND_HEADERS}
	@ mkdir -p build/
	${CPP_COMPILER} -c src/window-wayland.cpp -o build/window-wayland-debug.o ${CPP_DEBUG_OPTIONS}

# window.cpp (x11 variant)
build/window-x11.o: src/window-x11.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp src/uuid.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/window-x11.cpp -o build/window-x11.o ${CPP_RELEASE_OPTIONS}
build/window-x11-debug.o: src/window-x11.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp src/uuid.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/window-x11.cpp -o build/window-x11-debug.o ${CPP_DEBUG_OPTIONS}

# window.cpp (dummy variant)
build/window-dummy.o: src/window-dummy.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp src/uuid.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/window-dummy.cpp -o build/window-dummy.o ${CPP_RELEASE_OPTIONS}
build/window-dummy-debug.o: src/window-dummy.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp src/uuid.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/window-dummy.cpp -o build/window-dummy-debug.o ${CPP_DEBUG_OPTIONS}

# windowevents.cpp
build/windowevents.o: src/windowevents.cpp src/windowevents.hpp src/keyboard.hpp src/uuid.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/windowevents.cpp -o build/windowevents.o ${CPP_RELEASE_OPTIONS}
build/windowevents-debug.o: src/windowevents.cpp src/windowevents.hpp src/keyboard.hpp src/uuid.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/windowevents.cpp -o build/windowevents-debug.o ${CPP_DEBUG_OPTIONS}

# keyboard.cpp (glfw variant)
build/keyboard-glfw.o: src/keyboard-glfw.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/keyboard-glfw.cpp -o build/keyboard-glfw.o ${CPP_RELEASE_OPTIONS}
build/keyboard-glfw-debug.o: src/keyboard-glfw.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/keyboard-glfw.cpp -o build/keyboard-glfw-debug.o ${CPP_DEBUG_OPTIONS}

# keyboard.cpp (wayland variant)
build/keyboard-wayland.o: src/keyboard-wayland.cpp src/keyboard-common.cpp src/keyboard.hpp ${WAYLAND_HEADERS}
	@ mkdir -p build/
	${CPP_COMPILER} -c src/keyboard-wayland.cpp -o build/keyboard-wayland.o ${CPP_RELEASE_OPTIONS}
build/keyboard-wayland-debug.o: src/keyboard-wayland.cpp src/keyboard-common.cpp src/keyboard.hpp ${WAYLAND_HEADERS}
	@ mkdir -p build/
	${CPP_COMPILER} -c src/keyboard-wayland.cpp -o build/keyboard-wayland-debug.o ${CPP_DEBUG_OPTIONS}

# keyboard.cpp (x11 variant)
build/keyboard-x11.o: src/keyboard-x11.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/keyboard-x11.cpp -o build/keyboard-x11.o ${CPP_RELEASE_OPTIONS}
build/keyboard-x11-debug.o: src/keyboard-x11.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/keyboard-x11.cpp -o build/keyboard-x11-debug.o ${CPP_DEBUG_OPTIONS}

# keyboard.cpp (dummy variant)
build/keyboard-dummy.o: src/keyboard-dummy.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/keyboard-dummy.cpp -o build/keyboard-dummy.o ${CPP_RELEASE_OPTIONS}
build/keyboard-dummy-debug.o: src/keyboard-dummy.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/keyboard-dummy.cpp -o build/keyboard-dummy-debug.o ${CPP_DEBUG_OPTIONS}

# renderer.cpp (vulkan variant)
build/renderer-vulkan.o: src/renderer-vulkan.cpp src/renderer.hpp src/game.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/renderer-vulkan.cpp -o build/renderer-vulkan.o ${CPP_RELEASE_OPTIONS}
build/renderer-vulkan-debug.o: src/renderer-vulkan.cpp src/renderer.hpp src/game.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/renderer-vulkan.cpp -o build/renderer-vulkan-debug.o ${CPP_DEBUG_OPTIONS}

# renderer.cpp (gl variant)
build/renderer-gl.o: src/renderer-gl.cpp src/renderer.hpp src/game.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/renderer-gl.cpp -o build/renderer-gl.o ${CPP_RELEASE_OPTIONS}
build/renderer-gl-debug.o: src/renderer-gl.cpp src/renderer.hpp src/game.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/renderer-gl.cpp -o build/renderer-gl-debug.o ${CPP_DEBUG_OPTIONS}

# renderer.cpp (terminal variant)
build/renderer-terminal.o: src/renderer-terminal.cpp src/renderer.hpp src/game.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/renderer-terminal.cpp -o build/renderer-terminal.o ${CPP_RELEASE_OPTIONS}
build/renderer-terminal-debug.o: src/renderer-terminal.cpp src/renderer.hpp src/game.hpp
	@ mkdir -p build/
	${CPP_COMPILER} -c src/renderer-terminal.cpp -o build/renderer-terminal-debug.o ${CPP_DEBUG_OPTIONS}


# Build wayland headers
waylandHeaders: lib/wayland.h lib/wayland.c lib/xdg-shell.h lib/xdg-shell.c lib/xdg-toplevel-icon.h lib/xdg-toplevel-icon.c

# wayland-client headers
lib/wayland.h: ${WAYLAND_CORE_PROTOCOL}
	@ mkdir -p lib/
	${WAYLAND_SCANNER} client-header ${WAYLAND_CORE_PROTOCOL} lib/wayland.h

# wayland-client code
lib/wayland.c: ${WAYLAND_CORE_PROTOCOL}
	@ mkdir -p lib/
	${WAYLAND_SCANNER} private-code ${WAYLAND_CORE_PROTOCOL} lib/wayland.c

# xdg-shell headers
lib/xdg-shell.h: ${XDG_SHELL_PROTOCOL}
	@ mkdir -p lib/
	${WAYLAND_SCANNER} client-header ${XDG_SHELL_PROTOCOL} lib/xdg-shell.h

# xdg-shell code
lib/xdg-shell.c: ${XDG_SHELL_PROTOCOL}
	@ mkdir -p lib/
	${WAYLAND_SCANNER} private-code ${XDG_SHELL_PROTOCOL} lib/xdg-shell.c

# xdg-toplevel-icon headers
lib/xdg-toplevel-icon.h: ${XDG_TOPLEVEL_ICON_PROTOCOL}
	@ mkdir -p lib/
	${WAYLAND_SCANNER} client-header ${XDG_TOPLEVEL_ICON_PROTOCOL} lib/xdg-toplevel-icon.h

# xdg-toplevel-icon code
lib/xdg-toplevel-icon.c: ${XDG_TOPLEVEL_ICON_PROTOCOL}
	@ mkdir -p lib/
	${WAYLAND_SCANNER} private-code ${XDG_TOPLEVEL_ICON_PROTOCOL} lib/xdg-toplevel-icon.c


# Build wayland libs
waylandLibs: waylandHeaders build/wayland.o build/xdg-shell.o build/xdg-toplevel-icon.o

# wayland-client
build/wayland.o: lib/wayland.c
	@ mkdir -p build/
	${C_COMPILER} -c lib/wayland.c -o build/wayland.o ${C_RELEASE_OPTIONS}

# xdg-shell
build/xdg-shell.o: lib/xdg-shell.c
	@ mkdir -p build/
	${C_COMPILER} -c lib/xdg-shell.c -o build/xdg-shell.o ${C_RELEASE_OPTIONS}

# xdg-toplevel-icon
build/xdg-toplevel-icon.o: lib/xdg-toplevel-icon.c
	@ mkdir -p build/
	${C_COMPILER} -c lib/xdg-toplevel-icon.c -o build/xdg-toplevel-icon.o ${C_RELEASE_OPTIONS}


# Lint
lint:
	${LINTER} src/*.hpp src/*.cpp -header-filter=.* -- ${CPP_RELEASE_OPTIONS}


# Clean
clean:
	@ rm -rf build/ out/ lib/
