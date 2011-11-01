all: camera sender recv

camera: encoder/camera.cpp
	g++ `pkg-config --cflags opencv` `pkg-config --libs opencv` encoder/camera.cpp -o bin/camera

sender: encoder/sender.cpp
	g++ encoder/sender.cpp -o bin/sender

recv: decoder/recv.cpp
	g++ decoder/recv.cpp -o bin/recv

clean:
	rm bin/* 

