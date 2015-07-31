#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * dealrequest(char *a);


char * dealrequest(char *request)
{
	char *method=NULL;
	char *url=NULL;

	char *n=NULL;
	printf("%s\n",request);
	method=strtok(request," ");
	url=strtok(NULL," ");
	if(!url)
	{
		return n;
	}
	else
	{
		
	}
	
	
	if(strcmp(method,"GET")==0)
	{
		printf("%s",url);
	}	
	return n;
}


int main ()
{
char a[]={"GET / HTTP/1.1\r\nHost: 127.0.0.1:8888\r\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:38.0) Gecko/20100101 Firefox/38.0\r\n\r\n"};
char *c;
c=dealrequest(a);
//printf("c=%s\n",c);
free(c);
return 0;
}