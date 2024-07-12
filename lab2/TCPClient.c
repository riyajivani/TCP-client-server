#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

#define MAXLINESIZE 100
#define SERV_PORT 5555

int main(int argc, char** argv){
int connectsd;

char sendBuffer[MAXLINESIZE+1];
char recvBuffer[MAXLINESIZE+1];

struct sockaddr_in servaddr;
int noBytesRead=0;

	if(argc!=2){
		fprintf(stderr,"Usage %s IT-Address\n\n",argv[0]);
		exit(-1);
	}
	
	if ((connectsd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "Error creating socket\n");
        exit(-1);
    }
	
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	
	if(inet_pton(PF_INET,argv[1],&servaddr.sin_addr)<=0){
		fprintf(stderr,"error in inet_pton\n\n");
		exit(-1);
	}
	
	if(connect(connectsd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
		fprintf(stderr,"Error in connect\n\n");
		exit(-1);
	}
	
	for(;gets(sendBuffer)!=NULL;)
	{
		write(connectsd,sendBuffer,strlen(sendBuffer)+1);
		
		if(noBytesRead=read(connectsd,recvBuffer,sizeof(recvBuffer))<0){
			exit(0);
			
		}
		
		fprintf(stdout,"%s\n",recvBuffer);
	}
	
	return 0;	
}
