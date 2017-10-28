#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<pthread.h>
void *cwrite(void *cfd)
{		int i;
		char a[500];
		long mySock=(long)cfd;
		while(1)
		{	i=0;
			a[500]=0;
			printf("\n client  :");
			while((a[i++]=getchar())!='\n');
			if(a[0]=="0"){
			printf("\n client  exiting :\n");
			sleep(1);
			
			break;
			}	
			write(mySock,a, sizeof(a));
			sleep(1);
			
		}	pthread_exit(NULL);
}
void *cread(void *cfd)
{
	
	char a[500];
	long mySock=(long)cfd;
	while(1)
	{ 	a[500]=0;
		if(read(mySock,a,strlen(a))!=-1){
		if(a[0]=='0')
		{
		printf("\n other client : exiting \n");
		sleep(1);
		break;
		}
		printf("\n other client  : %s \n",a);
		sleep(1);	
		}
	}
pthread_exit(NULL);

}
int main(int arg,char *argv[]){

pthread_t t[2];
long client_sockfd;
sscanf(argv[0],"%ld",&client_sockfd);
	pthread_create(&t[0],NULL,&cread,(void*)client_sockfd);
	pthread_create(&t[1],NULL,&cwrite,(void*)client_sockfd);

pthread_exit(NULL);
}
