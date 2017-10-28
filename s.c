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
void *clientConnection(void *socket_desc)
{
    long mysock=(long)socket_desc;
    printf("client # %ld connected",mysock); 
    
//    free(socket_desc);
     
}

int main(int argc , char *argv[])
{
    long socket_desc;
    long new_socket;
    struct sockaddr_in server,client;
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("socket creation failure");
        return -1;
    }
     
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(9734);
     
    if(bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) ==-1)
    {
        puts("binding failure\n");
        return -1;
    }
    int p;
    listen(socket_desc,10);
	long socket1;
    int c=sizeof(struct sockaddr_in);    
    while(1)
    {
    	puts("Server Waiting\n");
    	socket1=accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
        char *c_ip = inet_ntoa(client.sin_addr);
    	printf("ip adress of the client is = %s \n",c_ip); 
         pthread_t thr;
         p=pthread_create(&thr,NULL,clientConnection,(void*)socket1);
        if(p==-1){
            printf("could not create thread");
            return 1;
        }
         
    }
     
    
    return 0;
}
 

