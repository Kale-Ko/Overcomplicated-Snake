# Project name and version
NAME=Overcomplicated-Snake
VERSION=v1.0.0
EXEC=${NAME}-${VERSION}

COMPILER=g++
RELEASE_OPTIONS=-O2
DEBUG_OPTIONS=-Og -g3

# Compiler options
CPP_OPTIONS=-I /usr/include/ -std=c++20
CPP_RELEASE_OPTIONS=
CPP_DEBUG_OPTIONS=-D SNAKE_DEBUG_INPUT
# Linker options
LN_OPTIONS=-L /usr/lib/ -l glfw -l wayland-client -l X11 -l vulkan -l GL
LN_RELEASE_OPTIONS=-s
LN_DEBUG_OPTIONS=

# Build all executables
build: buildRelease buildDebug
# Build all release executables
buildRelease: out/${EXEC}-glfw-vulkan out/${EXEC}-glfw-gl out/${EXEC}-x11-vulkan out/${EXEC}-x11-gl
# Build all debug executables
buildDebug: out/${EXEC}-glfw-vulkan-debug out/${EXEC}-glfw-gl-debug out/${EXEC}-x11-vulkan-debug out/${EXEC}-x11-gl-debug


# Main executable (glfw & vulkan variant)
out/${EXEC}-glfw-vulkan: build/main.o build/window-glfw.o build/windowevents.o build/keyboard-glfw.o build/renderer-vulkan.o
	@ mkdir -p out/
	${COMPILER} build/main.o build/window-glfw.o build/windowevents.o build/keyboard-glfw.o build/renderer-vulkan.o -o out/${EXEC}-glfw-vulkan ${RELEASE_OPTIONS} ${LN_OPTIONS} ${LN_RELEASE_OPTIONS}
out/${EXEC}-glfw-vulkan-debug: build/main-debug.o build/window-glfw-debug.o build/windowevents-debug.o build/keyboard-glfw-debug.o build/renderer-vulkan-debug.o
	@ mkdir -p out/
	${COMPILER} build/main-debug.o build/window-glfw-debug.o build/windowevents-debug.o build/keyboard-glfw-debug.o build/renderer-vulkan-debug.o -o out/${EXEC}-glfw-vulkan-debug ${DEBUG_OPTIONS} ${LN_OPTIONS} ${LN_DEBUG_OPTIONS}

# Main executable (wayland & vulkan variant)
out/${EXEC}-wayland-vulkan: build/main.o build/window-wayland.o build/windowevents.o build/keyboard-wayland.o build/renderer-vulkan.o
	@ mkdir -p out/
	${COMPILER} build/main.o build/window-wayland.o build/windowevents.o build/keyboard-wayland.o build/renderer-vulkan.o -o out/${EXEC}-wayland-vulkan ${RELEASE_OPTIONS} ${LN_OPTIONS} ${LN_RELEASE_OPTIONS}
out/${EXEC}-wayland-vulkan-debug: build/main-debug.o build/window-wayland-debug.o build/windowevents-debug.o build/keyboard-wayland-debug.o build/renderer-vulkan-debug.o
	@ mkdir -p out/
	${COMPILER} build/main-debug.o build/window-wayland-debug.o build/windowevents-debug.o build/keyboard-wayland-debug.o build/renderer-vulkan-debug.o -o out/${EXEC}-wayland-vulkan-debug ${DEBUG_OPTIONS} ${LN_OPTIONS} ${LN_DEBUG_OPTIONS}

# Main executable (x11 & vulkan variant)
out/${EXEC}-x11-vulkan: build/main.o build/window-x11.o build/windowevents.o build/keyboard-x11.o build/renderer-vulkan.o
	@ mkdir -p out/
	${COMPILER} build/main.o build/window-x11.o build/windowevents.o build/keyboard-x11.o build/renderer-vulkan.o -o out/${EXEC}-x11-vulkan ${RELEASE_OPTIONS} ${LN_OPTIONS} ${LN_RELEASE_OPTIONS}
out/${EXEC}-x11-vulkan-debug: build/main-debug.o build/window-x11-debug.o build/windowevents-debug.o build/keyboard-x11-debug.o build/renderer-vulkan-debug.o
	@ mkdir -p out/
	${COMPILER} build/main-debug.o build/window-x11-debug.o build/windowevents-debug.o build/keyboard-x11-debug.o build/renderer-vulkan-debug.o -o out/${EXEC}-x11-vulkan-debug ${DEBUG_OPTIONS} ${LN_OPTIONS} ${LN_DEBUG_OPTIONS}

# Main executable (glfw & gl variant)
out/${EXEC}-glfw-gl: build/main.o build/window-glfw.o build/windowevents.o build/keyboard-glfw.o build/renderer-gl.o
	@ mkdir -p out/
	${COMPILER} build/main.o build/window-glfw.o build/windowevents.o build/keyboard-glfw.o build/renderer-gl.o -o out/${EXEC}-glfw-gl ${RELEASE_OPTIONS} ${LN_OPTIONS} ${LN_RELEASE_OPTIONS}
out/${EXEC}-glfw-gl-debug: build/main-debug.o build/window-glfw-debug.o build/windowevents-debug.o build/keyboard-glfw-debug.o build/renderer-gl-debug.o
	@ mkdir -p out/
	${COMPILER} build/main-debug.o build/window-glfw-debug.o build/windowevents-debug.o build/keyboard-glfw-debug.o build/renderer-gl-debug.o -o out/${EXEC}-glfw-gl-debug ${DEBUG_OPTIONS} ${LN_OPTIONS} ${LN_DEBUG_OPTIONS}

# Main executable (wayland & gl variant)
out/${EXEC}-wayland-gl: build/main.o build/game.o build/window-wayland.o build/windowevents.o build/keyboard-wayland.o build/renderer-gl.o
	@ mkdir -p out/
	${COMPILER} build/main.o build/game.o build/window-wayland.o build/windowevents.o build/keyboard-wayland.o build/renderer-gl.o -o out/${EXEC}-wayland-gl ${RELEASE_OPTIONS} ${LN_OPTIONS} ${LN_RELEASE_OPTIONS}
out/${EXEC}-wayland-gl-debug: build/main-debug.o build/game-debug.o build/window-wayland-debug.o build/windowevents-debug.o build/keyboard-wayland-debug.o build/renderer-gl-debug.o
	@ mkdir -p out/
	${COMPILER} build/main-debug.o build/game-debug.o build/window-wayland-debug.o build/windowevents-debug.o build/keyboard-wayland-debug.o build/renderer-gl-debug.o -o out/${EXEC}-wayland-gl-debug ${DEBUG_OPTIONS} ${LN_OPTIONS} ${LN_DEBUG_OPTIONS}

# Main executable (x11 & gl variant)
out/${EXEC}-x11-gl: build/main.o build/game.o build/window-x11.o build/windowevents.o build/keyboard-x11.o build/renderer-gl.o
	@ mkdir -p out/
	${COMPILER} build/main.o build/game.o build/window-x11.o build/windowevents.o build/keyboard-x11.o build/renderer-gl.o -o out/${EXEC}-x11-gl ${RELEASE_OPTIONS} ${LN_OPTIONS} ${LN_RELEASE_OPTIONS}
out/${EXEC}-x11-gl-debug: build/main-debug.o build/game-debug.o build/window-x11-debug.o build/windowevents-debug.o build/keyboard-x11-debug.o build/renderer-gl-debug.o
	@ mkdir -p out/
	${COMPILER} build/main-debug.o build/game-debug.o build/window-x11-debug.o build/windowevents-debug.o build/keyboard-x11-debug.o build/renderer-gl-debug.o -o out/${EXEC}-x11-gl-debug ${DEBUG_OPTIONS} ${LN_OPTIONS} ${LN_DEBUG_OPTIONS}


# main.cpp
build/main.o: src/main.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/main.cpp -o build/main.o ${RELEASE_OPTIONS} ${CPP_OPTIONS} ${CPP_RELEASE_OPTIONS}
build/main-debug.o: src/main.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/main.cpp -o build/main-debug.o ${DEBUG_OPTIONS} ${CPP_OPTIONS} ${CPP_DEBUG_OPTIONS}

# game.cpp
build/game.o: src/game.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/game.cpp -o build/game.o ${RELEASE_OPTIONS} ${CPP_OPTIONS} ${CPP_RELEASE_OPTIONS}
build/game-debug.o: src/game.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/game.cpp -o build/game-debug.o ${DEBUG_OPTIONS} ${CPP_OPTIONS} ${CPP_DEBUG_OPTIONS}

# window.cpp (glfw variant)
build/window-glfw.o: src/window-glfw.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/window-glfw.cpp -o build/window-glfw.o ${RELEASE_OPTIONS} ${CPP_OPTIONS} ${CPP_RELEASE_OPTIONS}
build/window-glfw-debug.o: src/window-glfw.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/window-glfw.cpp -o build/window-glfw-debug.o ${DEBUG_OPTIONS} ${CPP_OPTIONS} ${CPP_DEBUG_OPTIONS}

# window.cpp (wayland variant)
build/window-wayland.o: src/window-wayland.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/window-wayland.cpp -o build/window-wayland.o ${RELEASE_OPTIONS} ${CPP_OPTIONS} ${CPP_RELEASE_OPTIONS}
build/window-wayland-debug.o: src/window-wayland.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/window-wayland.cpp -o build/window-wayland-debug.o ${DEBUG_OPTIONS} ${CPP_OPTIONS} ${CPP_DEBUG_OPTIONS}

# window.cpp (x11 variant)
build/window-x11.o: src/window-x11.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/window-x11.cpp -o build/window-x11.o ${RELEASE_OPTIONS} ${CPP_OPTIONS} ${CPP_RELEASE_OPTIONS}
build/window-x11-debug.o: src/window-x11.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/window-x11.cpp -o build/window-x11-debug.o ${DEBUG_OPTIONS} ${CPP_OPTIONS} ${CPP_DEBUG_OPTIONS}

# windowevents.cpp
build/windowevents.o: src/windowevents.cpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/windowevents.cpp -o build/windowevents.o ${RELEASE_OPTIONS} ${CPP_OPTIONS} ${CPP_RELEASE_OPTIONS}
build/windowevents-debug.o: src/windowevents.cpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/windowevents.cpp -o build/windowevents-debug.o ${DEBUG_OPTIONS} ${CPP_OPTIONS} ${CPP_DEBUG_OPTIONS}

# keyboard.cpp (glfw variant)
build/keyboard-glfw.o: src/keyboard-glfw.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/keyboard-glfw.cpp -o build/keyboard-glfw.o ${RELEASE_OPTIONS} ${CPP_OPTIONS} ${CPP_RELEASE_OPTIONS}
build/keyboard-glfw-debug.o: src/keyboard-glfw.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/keyboard-glfw.cpp -o build/keyboard-glfw-debug.o ${DEBUG_OPTIONS} ${CPP_OPTIONS} ${CPP_DEBUG_OPTIONS}

# keyboard.cpp (wayland variant)
build/keyboard-wayland.o: src/keyboard-wayland.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/keyboard-wayland.cpp -o build/keyboard-wayland.o ${RELEASE_OPTIONS} ${CPP_OPTIONS} ${CPP_RELEASE_OPTIONS}
build/keyboard-wayland-debug.o: src/keyboard-wayland.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/keyboard-wayland.cpp -o build/keyboard-wayland-debug.o ${DEBUG_OPTIONS} ${CPP_OPTIONS} ${CPP_DEBUG_OPTIONS}

# keyboard.cpp (x11 variant)
build/keyboard-x11.o: src/keyboard-x11.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/keyboard-x11.cpp -o build/keyboard-x11.o ${RELEASE_OPTIONS} ${CPP_OPTIONS} ${CPP_RELEASE_OPTIONS}
build/keyboard-x11-debug.o: src/keyboard-x11.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	${COMPILER} -c src/keyboard-x11.cpp -o build/keyboard-x11-debug.o ${DEBUG_OPTIONS} ${CPP_OPTIONS} ${CPP_DEBUG_OPTIONS}

# renderer.cpp (gl variant)
build/renderer-gl.o: src/renderer-gl.cpp src/renderer.hpp
	@ mkdir -p build/
	${COMPILER} -c src/renderer-gl.cpp -o build/renderer-gl.o ${RELEASE_OPTIONS} ${CPP_OPTIONS} ${CPP_RELEASE_OPTIONS}
build/renderer-gl-debug.o: src/renderer-gl.cpp src/renderer.hpp
	@ mkdir -p build/
	${COMPILER} -c src/renderer-gl.cpp -o build/renderer-gl-debug.o ${DEBUG_OPTIONS} ${CPP_OPTIONS} ${CPP_DEBUG_OPTIONS}

# renderer.cpp (vulkan variant)
build/renderer-vulkan.o: src/renderer-vulkan.cpp src/renderer.hpp
	@ mkdir -p build/
	${COMPILER} -c src/renderer-vulkan.cpp -o build/renderer-vulkan.o ${RELEASE_OPTIONS} ${CPP_OPTIONS} ${CPP_RELEASE_OPTIONS}
build/renderer-vulkan-debug.o: src/renderer-vulkan.cpp src/renderer.hpp
	@ mkdir -p build/
	${COMPILER} -c src/renderer-vulkan.cpp -o build/renderer-vulkan-debug.o ${DEBUG_OPTIONS} ${CPP_OPTIONS} ${CPP_DEBUG_OPTIONS}


# clean
clean:
	@ rm -rf build/ out/
