#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * deal(char *a);


char * deal(char *request)
{
	char *n=NULL;
	//char b[]="qqqqddssddsdsadaasddddddddddddddddddddddddddddddddddqqqqqreqqqq";
	//n=(char *)malloc(sizeof(b));
	//strcpy(n,b);
	printf("%s\n",request);
	char *p;
	p=strtok(request,"8");
	printf("\n%s\n",p );

	p=strtok(NULL,"8");
	printf("\n%s\n",p );
	return n;
}


int main ()
{
char a[]={"GET / HTTP/1.1\r\nHost: 127.0.0.1:8888\r\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:38.0) Gecko/20100101 Firefox/38.0\r\n\r\n"};
char *c;
c=deal(a);
//printf("c=%s\n",c);
free(c);
return 0;
}