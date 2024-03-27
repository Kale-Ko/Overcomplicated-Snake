# Project name and version
NAME=Overcomplicated-Snake
VERSION=v1.0.0
EXEC=${NAME}-${VERSION}

# Compiler options
CPP_OPTIONS=-I/usr/include -std=c++20
# Linker options
LN_OPTIONS=-L/usr/lib -l glfw -l wayland-client -l X11 -l vulkan -l GL


# Build all executables
build: buildRelease buildDebug
# Build all release executables
buildRelease: out/${EXEC}-glfw out/${EXEC}-x11
# Build all debug executables
buildDebug: out/${EXEC}-glfw-debug out/${EXEC}-x11-debug


# Main executable (glfw variant)
out/${EXEC}-glfw: build/main.o build/window-glfw.o build/windowevents.o build/keyboard-glfw.o
	@ mkdir -p out/
	g++ build/main.o build/window-glfw.o build/windowevents.o build/keyboard-glfw.o -o out/${EXEC}-glfw ${LN_OPTIONS} -O2
out/${EXEC}-glfw-debug: build/main-debug.o build/window-glfw-debug.o build/windowevents-debug.o build/keyboard-glfw-debug.o
	@ mkdir -p out/
	g++ build/main-debug.o build/window-glfw-debug.o build/windowevents-debug.o build/keyboard-glfw-debug.o -o out/${EXEC}-glfw-debug ${LN_OPTIONS} -Og -g3

# Main executable (wayland variant)
out/${EXEC}-wayland: build/main.o build/window-wayland.o build/windowevents.o build/keyboard-wayland.o
	@ mkdir -p out/
	g++ build/main.o build/window-wayland.o build/windowevents.o build/keyboard-wayland.o -o out/${EXEC}-wayland ${LN_OPTIONS} -O2
out/${EXEC}-wayland-debug: build/main-debug.o build/window-wayland-debug.o build/windowevents-debug.o build/keyboard-wayland-debug.o
	@ mkdir -p out/
	g++ build/main-debug.o build/window-wayland-debug.o build/windowevents-debug.o build/keyboard-wayland-debug.o -o out/${EXEC}-wayland-debug ${LN_OPTIONS} -Og -g3

# Main executable (x11 variant)
out/${EXEC}-x11: build/main.o build/window-x11.o build/windowevents.o build/keyboard-x11.o
	@ mkdir -p out/
	g++ build/main.o build/window-x11.o build/windowevents.o build/keyboard-x11.o -o out/${EXEC}-x11 ${LN_OPTIONS} -O2
out/${EXEC}-x11-debug: build/main-debug.o build/window-x11-debug.o build/windowevents-debug.o build/keyboard-x11-debug.o
	@ mkdir -p out/
	g++ build/main-debug.o build/window-x11-debug.o build/windowevents-debug.o build/keyboard-x11-debug.o -o out/${EXEC}-x11-debug ${LN_OPTIONS} -Og -g3


# main.cpp
build/main.o: src/main.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/main.cpp -o build/main.o ${CPP_OPTIONS} -O2
build/main-debug.o: src/main.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/main.cpp -o build/main-debug.o ${CPP_OPTIONS} -Og -g3

# window.cpp (glfw variant)
build/window-glfw.o: src/window-glfw.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/window-glfw.cpp -o build/window-glfw.o ${CPP_OPTIONS} -O2
build/window-glfw-debug.o: src/window-glfw.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/window-glfw.cpp -o build/window-glfw-debug.o ${CPP_OPTIONS} -Og -g3

# window.cpp (wayland variant)
build/window-wayland.o: src/window-wayland.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/window-wayland.cpp -o build/window-wayland.o ${CPP_OPTIONS} -O2
build/window-wayland-debug.o: src/window-wayland.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/window-wayland.cpp -o build/window-wayland-debug.o ${CPP_OPTIONS} -Og -g3

# window.cpp (x11 variant)
build/window-x11.o: src/window-x11.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/window-x11.cpp -o build/window-x11.o ${CPP_OPTIONS} -O2
build/window-x11-debug.o: src/window-x11.cpp src/window.hpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/window-x11.cpp -o build/window-x11-debug.o ${CPP_OPTIONS} -Og -g3

# windowevents.cpp
build/windowevents.o: src/windowevents.cpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/windowevents.cpp -o build/windowevents.o ${CPP_OPTIONS} -O2
build/windowevents-debug.o: src/windowevents.cpp src/windowevents.hpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/windowevents.cpp -o build/windowevents-debug.o ${CPP_OPTIONS} -Og -g3

# keyboard.cpp (glfw variant)
build/keyboard-glfw.o: src/keyboard-glfw.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/keyboard-glfw.cpp -o build/keyboard-glfw.o ${CPP_OPTIONS} -O2
build/keyboard-glfw-debug.o: src/keyboard-glfw.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/keyboard-glfw.cpp -o build/keyboard-glfw-debug.o ${CPP_OPTIONS} -Og -g3

# keyboard.cpp (wayland variant)
build/keyboard-wayland.o: src/keyboard-wayland.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/keyboard-wayland.cpp -o build/keyboard-wayland.o ${CPP_OPTIONS} -O2
build/keyboard-wayland-debug.o: src/keyboard-wayland.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/keyboard-wayland.cpp -o build/keyboard-wayland-debug.o ${CPP_OPTIONS} -Og -g3

# keyboard.cpp (x11 variant)
build/keyboard-x11.o: src/keyboard-x11.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/keyboard-x11.cpp -o build/keyboard-x11.o ${CPP_OPTIONS} -O2
build/keyboard-x11-debug.o: src/keyboard-x11.cpp src/keyboard-common.cpp src/keyboard.hpp
	@ mkdir -p build/
	g++ -c src/keyboard-x11.cpp -o build/keyboard-x11-debug.o ${CPP_OPTIONS} -Og -g3


# clean
clean:
	@ rm -rf build/ out/
