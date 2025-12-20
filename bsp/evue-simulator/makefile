quickjs:
	rm -rf build
	mkdir build
	cd build && qmake ../app/app.pro DEFINES+=EVM_USE_QUICKJS && make -j8

mujs:
	rm -rf build
	mkdir build
	cd build && qmake ../app/app.pro DEFINES+=EVM_USE_MUJS && make -j8

pika:
	rm -rf build
	mkdir build
	cd build && qmake ../app/app.pro DEFINES+=EVM_USE_PIKASCRIPT && make -j8

	



