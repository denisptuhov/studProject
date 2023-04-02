#include <iostream> // cout
#include <cstring> // strerror

#include <sys/stat.h> // For mode constants
#include <fcntl.h> // For O_* constants
#include <sys/mman.h> // shm_open, mmap

int main(){
	const int capacity = 1000;
	char* name = new char[13];
	
	std::cin >> name;
	
	int fd = shm_open(name, O_RDONLY, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH));
	if (fd <= 0){
		fprintf(stderr, "shm_open(%s): %s (%d)\n", name, std::strerror(errno), errno);
		return 0;
	}
					 
	auto data = (unsigned char*)mmap(NULL, capacity, PROT_READ, MAP_SHARED, fd, 0);
	if (data == MAP_FAILED){
		fprintf(stderr, "mmap(%s, %d): %s (%d)\n", name, capacity, std::strerror(errno), errno);
		return 0;
	}
	
	std::cout << data << std::endl;
	
	shm_unlink(name);
	delete[] name;
	
	return 0;
}