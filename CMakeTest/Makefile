
all: unix

unix: GENERATOR = "Unix Makefiles"
unix: build
	make -C build

build:
	mkdir build
	cd build && cmake -G $(GENERATOR) ..

clean:
	@echo "[CLEAN]"
	@rmdir /s /q build