#include "devport.h"
#include <string.h>
#include <stdio.h>

int check_arg(char *arg, int a)
{
	int value = 0;
	int len;
	int i;
	int tmp;
	tmp = 1;
	len = strlen(arg);
	//printf("%c, length is: %d\n", *arg, len);
	if((*arg != '0') || (*(++arg) != 'x')) {
		printf("port format wrong, should begin with 0x, like 0xffff!\n");
		return -1;
	}
	len -= 2;
	while(*(++arg) != '\0') {
		switch(*arg) {
			case '0':
				for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*0;
				tmp = 1;
				len--;
				break;
			case '1':
				for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*1;
				tmp = 1;
				len--;
				break;
			case '2':
				for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*2;
				tmp = 1;
				len--;
				break;
			case '3':
				for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*3;
				tmp = 1;
				len--;
				break;
			case '4':
				for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*4;
				tmp = 1;
				len--;
				break;
			case '5':
				for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*5;
				tmp = 1;
				len--;
				break;
			case '6':
				for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*6;
				tmp = 1;
				len--;
				break;
			case '7':

					for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*7;
				tmp = 1;
				len--;
				break;
			case '8':
				for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*8;
				tmp = 1;
				len--;
				break;
			case '9':
				for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*9;
				tmp = 1;
				len--;
				break;
			case 'a':
				for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*10;
				tmp = 1;
				len--;
				break;
			case 'b':
				for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*11;
				tmp = 1;
				len--;
				break;
			case 'c':
				for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*12;
				tmp = 1;
				len--;
				break;
			case 'd':
				for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*13;
				tmp = 1;
				len--;
				break;
			case 'e':
				for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*14;
				tmp = 1;
				len--;
				break;
			case 'f':
				for(i=0; i<len-1; i++) {
					tmp *=16; 
				}
				value += tmp*15;
				tmp = 1;
				len--;
				break;
		}
	}
	
	return value;
}
