build/hello.bin: build/Makefile *.c
	cd build && make

build/Makefile:
	mkdir -p build
	cd build && cmake ..

clean:
	rm -rf build
