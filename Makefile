appname := myapp

srcfiles := $(shell find . -maxdepth 1 -name "*.cpp")
all:
	make setup
	make compile
	make run

setup:
	mkdir -p build

compile:
	LDFLAGS="-L/usr/local/opt/ncurses/lib"
	CPPFLAGS="-I/usr/local/opt/ncurses/include"
	g++ $(srcfiles) -o build/app -lncurses

run:
	build/app