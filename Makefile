# In makefiles, the default script is the topmost one. Run using `$ make`
build-and-run:
	@# Compile main.cpp
	g++ -c src/main.cpp

	@# Link the compiled object file with SFML libraries
	g++ main.o -o build/tetris -lsfml-graphics -lsfml-window -lsfml-system

	@# Finally, run main
	./build/tetris

