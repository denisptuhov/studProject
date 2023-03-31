#include <iostream>
#include <cerrno>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

int main(){
	char const* name = "SharedMemory";
	int fd = shm_open(name, O_CREAT | O_RDWR, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH));
	
	if (fd <= 0){
		std::cout << std::strerror(errno) << std::endl;
		return 0;
	}
	
	int res = fchmod(fd, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH));
	if (res != 0){
		std::cout << std::strerror(errno) << std::endl;
		return 0;
	}
	
	int capacity = 1000;
	res = ftruncate(fd, capacity);
	if (res != 0){
		std::cout << std::strerror(errno) << std::endl;
		return 0;
	}
	
	auto data = (unsigned char*)mmap(NULL, capacity, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (data == MAP_FAILED){
		std::cout << std::strerror(errno) << std::endl;
		return 0;
	}
	
	unsigned char arr[13] = "Hello World!";
	
	std::memcpy(data, arr, 13);
	std::cout << fd;
	
	return 0;
}