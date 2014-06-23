all: imports/Hipsta imports/Synergy

imports:
	mkdir imports

imports/Hipsta: imports
	cd hipstamouse; ../../output/host/usr/bin/qmake; make -j4; cp -R ./imports/Hipsta ../imports; cd ..

imports/Synergy: imports
	cd serialmon; ../../output/host/usr/bin/qmake; make -j4; cp -R ./imports/Synergy ../imports; cd ..

install: all
	mkdir -p ../overlay-rpiduino/usr/qml/
	cp -R ./imports/* ../overlay-rpiduino/usr/qml/
