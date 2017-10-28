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
 
void *Sclient(void * id)
{
printf("thread called \n");
    long socket_desc;
    
    struct sockaddr_in server,client;
     
    socket_desc= socket(AF_INET,SOCK_STREAM,0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    } 
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(8800);
    
    connect(socket_desc,(struct sockaddr *)&server, sizeof(server));
    bind(socket_desc,(struct sockaddr *)&server,sizeof(server)); 
    listen(socket_desc,10);
  long socket1;
  int c=sizeof(struct sockaddr_in);
    while(1)
    {
    socket1= accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    char *c_ip = inet_ntoa(client.sin_addr);
    printf("ip adress of the client is = %s \n",c_ip);
   
      pid_t result;
      result=fork();
      if(result==0)
      {printf("fork called");
        char buffer[BUFSIZ+1];
        memset(buffer, '\0', sizeof(buffer));
        sprintf(buffer, "%ld",socket1);
        char* terminal[]={"/usr/bin/xterm", "-e", "/home/ali/Desktop/ter.o",buffer, NULL};
        execvp("/usr/bin/xterm",terminal);
      }
     }  
    
   /* pthread_t thr;
    new_sock = malloc(1);
   *new_sock = new_socket1;
   
   pthread_create( &thr,NULL,Sclient,(void*)new_sock);
   */
    pthread_exit(NULL);
    close(socket_desc);
}/*
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
  */
int main(int argc , char *argv[])
{
    int socket_desc;
    struct sockaddr_in server,client;
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if(socket_desc == -1)
    {
        printf("Could not create socket");
    }   
    server.sin_addr.s_addr = inet_addr("192.168.220.140");
    server.sin_family = AF_INET;
    server.sin_port = htons(9734);
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) ==-1)
    {
        printf(" error connect to main server \n");
        return 0;
    }
        
    pthread_t cthread;
    pthread_create(&cthread,NULL,Sclient,NULL); 
    
    
     char ip[100];
     long socket_fd;
     printf("enter the ip address to connect to ther other client =");
     scanf("%99s",ip);
    socket_fd= socket(AF_INET,SOCK_STREAM,0);
    if (socket_fd==-1)
    {
        printf(" socket creation error \n");
    }
    client.sin_addr.s_addr = inet_addr(ip);
    client.sin_family = AF_INET;
    client.sin_port = htons(8800);
    int c;
    if (connect(socket_fd,(struct sockaddr *)&client,sizeof(client)) == -1)
    {
        printf("error connecting to other client ");
        return 0;
    }    
    int res;
    res=fork();
      if(res==0)
      {printf("fork called\n");
        char buffer[BUFSIZ+1];
        memset(buffer, '\0', sizeof(buffer));
        sprintf(buffer, "%ld",socket_fd);
        char* terminal[]={"/usr/bin/xterm", "-e", "/home/ali/Desktop/ter.o",buffer, NULL};
        execvp("/usr/bin/xterm",terminal);
      }
       
    close(socket_desc);
}

