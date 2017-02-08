flags = -Wall -std=c++11
paths = src/*.o
app_name = app

all:
	cd src; make
	g++ main.cpp $(paths) -o $(app_name) $(flags)

clean:
	cd src; make clean
	rm $(app_name)
