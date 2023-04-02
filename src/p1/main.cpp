#include <iostream> // cout
#include <cstring> // memcpy

#include <sys/stat.h> // For mode constants
#include <fcntl.h> // For O_* constants
#include <sys/mman.h> // shm_open, mmap
#include <unistd.h> // ftruncate

int main(){
	char const* name = "SharedMemory";
	int fd = shm_open(name, O_CREAT | O_RDWR, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH));
		
	if (fd <= 0){
		fprintf(stderr, "shm_open(%s): %s (%d)\n", name, std::strerror(errno), errno);
		return 0;
	}

	const int capacity = 1000;
	int res = ftruncate(fd, capacity);
	if (res != 0){
		fprintf(stderr, "ftruncate: %s (%d)\n", std::strerror(errno), errno);
		return 0;
	}
	
	auto data = (unsigned char*)mmap(NULL, capacity, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (data == MAP_FAILED){
		fprintf(stderr, "mmap(%s, %d): %s (%d)\n", name, capacity, std::strerror(errno), errno);
		return 0;
	}
	
	unsigned char arr[13] = "Hello World!";
	
	std::memcpy(data, arr, 13);
	std::cout << name;
	
	return 0;
}