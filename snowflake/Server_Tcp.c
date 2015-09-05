#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdlib.h>

#define SERV_PORT 6660
#define SERV_IP "123.59.50.13"
#define BACKLOG 10
#define MAXBUFSIZE 200
char buf[MAXBUFSIZE];
char str_to_send[MAXBUFSIZE] = "important notice:to cerebrate China log on moon successful on 12								nd, Jan, 2010 everyone has a day free from work!\n";

int main()
{
	int sockfd,sockfd_client;
	socklen_t sin_size;
	fprintf(stdout, "################################\n");
	fprintf(stdout, "server ip:%s port:%d\n",SERV_IP, SERV_PORT);
	fprintf(stdout, "################################\n");
	struct sockaddr_in my_addr;
	struct sockaddr_in serv_addr, client_sockaddr;
	int serverport;
	serverport = SERV_PORT;
	if( (sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1 )
	{
		perror("error in create socket/n");
		exit(0);
	}
	fprintf(stdout, "create socket\n");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(6660);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&serv_addr.sin_zero, 8);
	if( bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1 )
	{
		perror("bind error\n");
		exit(0);
	}
	fprintf(stdout, "bind successful\n");
	if( listen(sockfd, BACKLOG) == -1)
	{
		perror("listenning");
		exit(1);
	}
	fprintf(stdout, "the server is listenning.....\n");
	fprintf(stdout, "before accept:sockfd_client is %d\n",sockfd_client);

	if( (sockfd_client = accept(sockfd, (struct sockaddr *)&client_sockaddr, &sin_size)) == -1 )
	{
		perror("accept");
		exit(1);
	}
	fprintf(stdout, "accept connect\n");

	int recvbytes;
	if( (recvbytes=recv(sockfd_client, buf, MAXBUFSIZE,0)) == -1 )
	{
		perror("receive");
		exit(1);
	}
	fprintf(stdout, "%dbytes receive from connect:%s\n",recvbytes, buf);
	close(sockfd);
	close(sockfd_client);
	return 0;
}





















