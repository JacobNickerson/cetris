# In makefiles, the default script is the topmost one. Run using `$ make`
build-and-run:
	@# Compile main.cpp
	g++ -I include/ src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o build/cetris

	@# Finally, run main
	./build/cetris

# compiles program and runs using gdb
gdb:
	@# Compile main.cpp
	g++ -g -I include/ src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o build/cetris

	@# Finally, run main
	gdb ./build/cetris

# runs program without compiling
run:
	./build/cetris
