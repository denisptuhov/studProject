#include <cstdio>
#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

int main(){
	char const* name = "/mem_ex.shm";
	int fd = shm_open(name, O_CREAT | O_RDWR,
                     (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH));
	
	if (fd <= 0)
		return 0;
	
	int res = fchmod(fd, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH));
	if (res != 0){
		shm_unlink(name);
		return 0;
	}
	
	struct stat fileStat;
	res = fstat(fd, &fileStat);
	if (res != 0){
		shm_unlink(name);
		return 0;
	}
	
	int capacity = 1000;
	res = ftruncate(fd, capacity);
	if (res != 0){
		shm_unlink(name);
		return 0;
	}
	
	auto data = (char*)mmap(NULL, capacity, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (data == MAP_FAILED){
		shm_unlink(name);
		return 0;
	}
	
	char arr[13] = "Hello World!";
	
	std::memcpy(data, arr, 13);
	std::cout << data;
	
	
}