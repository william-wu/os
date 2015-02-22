#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    struct rlimit sl, pl, fl;
	if (getrlimit(RLIMIT_STACK, &sl) == -1) {
		printf("shit happened\n");
		return -1;
	}
	printf("stack size:%lld\n", (long long int) sl.rlim_cur/1024);
    
	if (getrlimit(RLIMIT_NPROC, &pl) == -1) {
		printf("shit happened\n");
		return -1;
	}
	printf("process limit: %lld\n", (long long int)pl.rlim_cur);
	
	if (getrlimit(RLIMIT_NOFILE, &fl) == -1) {
		printf("shit happened\n");
		return -1;
	}
    printf("max file descriptors: %lld\n", (long long int)fl.rlim_cur);
}
