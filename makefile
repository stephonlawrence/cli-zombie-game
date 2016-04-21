appname := myapp

srcfiles := $(shell find . -maxdepth 1 -name "*.cpp")
all:
	g++ $(srcfiles) -o build/app -lncurses
	build/app
