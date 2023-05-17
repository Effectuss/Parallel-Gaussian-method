all: build

build: install

rebuild: clean install

install:
	cmake -S . -B ./build
	cmake --build ./build
	

run:
	cd build; ./ParallelGaussianMethod

clean:
	@rm -rf build

cppcheck: install
	cmake --build build --target cppcheck

clang-format: install
	cmake --build build --target clangformat
	