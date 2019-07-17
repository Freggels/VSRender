#!/bin/sh

LIBS="-lvulkan -lvulkan_radeon -lglfw -Iinclude"
OUTPUT_FILE="main"

build() {
	mkdir ./binary > /dev/null
	printf "[ BUILD STAGE ]\n"
	printf "[compiling shader.vert]..."
	if [ "$(cat shaders/.shader.vert.mdfy)" != "$(stat -c "%Y" shaders/shader.vert)" ]; then
		glslangValidator -V shaders/shader.vert -o binary/vert.spv || exit
		stat -c "%Y" shaders/shader.vert > shaders/.shader.vert.mdfy;
		echo changed shaders
	else
		echo "shaders/shader.vert"
	fi
	printf "[compiling shader.frag]..."
	if [ "$(cat shaders/.shader.frag.mdfy)" != "$(stat -c "%Y" shaders/shader.frag)" ]; then
		glslangValidator -V shaders/shader.frag -o binary/frag.spv || exit
		stat -c "%Y" shaders/shader.frag > shaders/.shader.frag.mdfy;
		echo changed shaders
	else
		echo "shaders/shader.vert"
	fi
	if [ "$2" = "--shaders-only" ]; then
		exit
	fi
	if [ "$2" = "-F" ]; then
		FORCE="1"
	elif [ ! -f ./$OUTPUT_FILE ]; then
		FORCE="1"
	elif [ "$(cat include/.config.h.mdfy)" != "$(stat -c "%Y" include/config.hpp)" ]; then
		FORCE="1"
		stat -c "%Y" include/config.hpp > include/.config.h.mdfy
	elif [ "$(cat include/.render_font.h.mdfy)" != "$(stat -c "%Y" include/render_font.hpp)" ]; then
		FORCE="1"
		stat -c "%Y" include/render_font.hpp > include/.render_font.h.mdfy
	elif [ "$(cat include/.render.h.mdfy)" != "$(stat -c "%Y" include/render.hpp)" ]; then
		FORCE="1"
		stat -c "%Y" include/render.hpp > include/.render.h.mdfy
	elif [ "$(cat include/.render_tools.h.mdfy)" != "$(stat -c "%Y" include/render_tools.hpp)" ]; then
		FORCE="1"
		stat -c "%Y" include/render_tools.hpp > include/.render_tools.h.mdfy
	fi
	printf "[compiling render.cpp]..."
	mdfy="$(stat -c "%Y" src/render.cpp)"
	if [ "$(cat src/.render.mdfy)" != "$mdfy" ] || [ "$FORCE" = "1" ]; then
		g++ -std=c++17 -c src/render.cpp -o binary/render.o $LIBS || exit
		echo $mdfy > src/.render.mdfy
		REBUILDED="1"
	fi
	echo "binary/render.o"

	printf "[compiling render_tools.cpp]..."
	mdfy="$(stat -c "%Y" src/render_tools.cpp)"
	if [ "$(cat src/.render_tools.mdfy)" != "$mdfy" ] || [ "$FORCE" = "1" ]; then
		g++ -std=c++17 -c src/render_tools.cpp -o binary/render_tools.o $LIBS || exit
		echo $mdfy > src/.render_tools.mdfy
		REBUILDED="1"
	fi
	echo "binary/render_tools.o"

	printf "[compiling render_font.cpp]..."
	mdfy="$(stat -c "%Y" src/render_font.cpp)"
	if [ "$(cat src/.render_font.mdfy)" != "$mdfy" ] || [ "$FORCE" = "1" ]; then
		g++ -std=c++17 -c src/render_font.cpp -o binary/render_font.o $LIBS || exit
		echo $mdfy > src/.render_font.mdfy
		REBUILDED="1"
	fi
	echo "binary/render_font.o"

	printf "[compiling main.cpp]..."
	mdfy="$(stat -c "%Y" src/main.cpp)"
	if [ "$(cat src/.main.mdfy)" != "$mdfy" ] || [ "$FORCE" = "1" ]; then
		g++ -std=c++17 -c src/main.cpp -o binary/main.o $LIBS || exit
		echo $mdfy > src/.main.mdfy
		REBUILDED="1"
	fi
	echo "binary/main.o"

	printf "[linking to main]..."
	if [ "$REBUILDED" = "1" ]; then
		g++ -std=c++17 -o "./$OUTPUT_FILE" $LIBS \
			binary/render.o \
			binary/render_tools.o \
			binary/render_font.o \
			binary/main.o
	fi
	echo "$OUTPUT_FILE" || exit
}

run() {
	printf "[ RUN STAGE ]\n"
	printf "[executing ./$OUTPUT_FILE]\n"
	sh -c ./$OUTPUT_FILE && (
		printf "[exited with success]\n"
	) || (
		printf "[exited with error]\n"
	)
}

for arg in "$@"; do
	if [ "$arg" = "-F" ]; then
		export FORCE="1"
	fi
	if [ "$arg" = "-b" ]; then
		build $@
	fi
	if [ "$arg" = "-r" ]; then
		run
	fi

done
