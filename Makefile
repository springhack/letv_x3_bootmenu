all:
	arm-none-linux-gnueabi-g++ --static -pthread -fpermissive main.cpp -o fbb
