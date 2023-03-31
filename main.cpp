#include <cstdio>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>

void* createSharedMemory(char const* name = "/mem_ex.shm")
{
    int fd = shm_open(name, O_CREAT | O_RDWR,
                      (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH));
	
	if (fd <= 0)
		return nullptr;
	
	int res = fchmod(fd, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH));
	if (res != 0){
		shm_unlink(name);
		return nullptr;
	}
	
	struct stat fileStat;
	res = fstat(fd, &fileStat);
	if (res != 0){
		shm_unlink(name);
		return nullptr;
	}
	
	std::cout << fd << std::endl;

}

int main(){
	createSharedMemory();
}