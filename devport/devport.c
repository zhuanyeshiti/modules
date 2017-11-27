#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <malloc.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "devport.h"

int main(int argc, char *argv[])
{
	int i;
	int fd;
	int result, cmd_code;
	int *a;
	int *b;
	int childpid;

	uid_t uid;
	uid = getuid();
	if(uid == 0) {
		goto skip_fork;
	}
	if(fork() == 0) {
		if(execl("/bin/sh", "sh", "-c", "sudo -s", (char *)0) < 0)
		{
			printf("fork fail !\n");
			exit(0);
		}
	}
	else {
		wait(&childpid);
		printf("child has done what she should do!\n");
		return 0;
	}
skip_fork:
	a = (int *)malloc(200);
	memset(a, 0, 200);
	b = a;
	*a = 0x80;
	/*
	* for(i=0; i<argc; i++)
	* {
	*	printf("arg%dis: %s\n", i, argv[i]);
	* }
	*/
	fd = open("/dev/memdev", O_RDWR);
	if(fd < 0)
	{
		printf("error open\n");
	}
	*a = check_arg(argv[1], 1);
	//printf("%d\n", *a);
	//*a = atoi(argv[1]);
	switch(*argv[2]) {
		case 'b':
			cmd_code = 0;
			break;
		case 'w':
			cmd_code = 1;
			break;
		case 'l':
			cmd_code = 3;
			b++;
			*b = check_arg(argv[3], 1);
			printf("write 0x%x to port: 0x%x\n", *(a+1), *a);
			//printf("argv3 = %s\n", argv[3]);
			//printf("write data is: %d\n", *(a+1));
			break;
		default:
			printf("wrong cmd_code, return!\n");
			close(fd);
			return 0;
	}
	printf("port is 0x%x\n", *a);
	result = ioctl(fd, cmd_code, a);
	printf("value is 0x%x\n", *a);
	if(result < 0)
	{
		printf("error ioctl\n");
	}
	close(fd);
	return 0;
}
