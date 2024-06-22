# In makefiles, the default script is the topmost one. Run using `$ make`
build-and-run:
	@# Compile main.cpp
	g++ -I include/ src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -o build/tetris

	@# Finally, run main
	./build/tetris

