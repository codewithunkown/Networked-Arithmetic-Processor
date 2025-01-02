/*Required Header Files*/
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h> 
#include<error.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<ctype.h>
#include<string.h>
#include<limits.h>

/*Macro*/
#define PORTMIN 1024
#define PORTMAX 65535

/*Colour Macros*/
#define END "\033[0m" //end
#define RED "\033[31m"//redForeground
#define GREEN "\033[32m"//greenForeground
#define GRAYBG "\033[100m" //grayBackground
#define BLUEU "\033[4m\033[34m"//blueUnderline
#define GREENB "\033[5m\033[92m"//greenForegroundBlink 
#define GREENWFG "\033[32m\033[107m"//greenWhiteForeground
/*Structure*/
struct st 
{
	char Op;
	long Num1, Num2;
} data;