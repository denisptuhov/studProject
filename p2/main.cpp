#include <cstdio>
#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

int main(){
	int fd, capacity = 1000;
	char const* name = "SharedMemory";
	
	std::cin >> fd;
	
	shm_open(name, O_RDWR, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH));
					 
	auto data = (unsigned char*)mmap(NULL, capacity, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (data == MAP_FAILED){
		std::cout << std::strerror(errno) << std::endl;
		return 0;
	}
	
	
	std::cout << data << std::endl;
	
}