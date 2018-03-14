all:
	mkdir bin/
	g++ -o bin/stpb src/stpb.cpp
clean:
	rm bin/*
