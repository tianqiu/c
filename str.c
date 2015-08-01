#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * dealrequest(char *a);


char * dealrequest(char *request)
{
	char *response=NULL;
	char *method=NULL;
	char *url=NULL;
	char *n=NULL;
	printf("%s\n",request);
	method=strsep(&request," ");
	url=strsep(&request," ");
	printf("%s\n",method );
	printf("%s",url);
	schedule_timeout_uninterruptible(11111000)
	if(!url)
	{
		return n;
	}
	if (strcmp(url,"/")==0)
	{
		printf("\nsadasdasda");
	}
	
	
	if(strcmp(method,"GET")==0)
	{
		//printf("%s",url);
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
c=NULL;
return 0;
}