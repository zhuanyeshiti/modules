#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[])
{
	int i;
	int fd;
	int result;
	for(i=0; i<argc; i++)
	{
		printf("arg%dis: %s\n", i, argv[i]);
	}
	fd = open("/dev/memdev", O_RDWR);
	if(fd < 0)
	{
		printf("error open\n");
	}
	result = ioctl(fd, 3, "al_args");
	if(result < 0)
	{
		printf("error ioctl\n");
	}
	close(fd);
	return 0;
}
