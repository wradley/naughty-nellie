flags = -Wall -std=c++11
paths = src/*.o src/systems/*.o src/util/*.o
app_name = app

all:
	cd src; make
	cd src/systems; make
	cd src/util; make
	g++ main.cpp $(paths) -o $(app_name) $(flags)

clean:
	cd src; make clean
	cd src/systems; make clean
	cd src/util; make clean
	rm $(app_name)
