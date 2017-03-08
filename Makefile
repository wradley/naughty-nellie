flags = -Wall -std=c++11  -lSDL2 -lSDL2_image
paths = src/*.o src/systems/*.o src/util/*.o src/util/Messaging/*.o
app_name = app

all:
	cd src; make
	cd src/systems; make
	cd src/util; make
	cd src/util/Messaging; make
	g++ main.cpp $(paths) -o $(app_name) $(flags)

clean:
	cd src; make clean
	cd src/systems; make clean
	cd src/util; make clean
	cd src/util/Messaging; make clean
	rm $(app_name)
