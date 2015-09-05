#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main()
{
	struct sockaddr_in s_addr,c_addr;
	int sock;
	socklen_t addr_len;
	int len;
	char buff[128];

	if( (sock=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		perror("socket");
		exit(errno);
	}
	else
	{
		printf("Creat socket.\n\r");
	}
	memset(&s_addr,0,sizeof(struct sockaddr_in));
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(6660);
	s_addr.sin_addr.s_addr = INADDR_ANY;
	if( (bind(sock, (struct sockaddr *)&s_addr, sizeof(s_addr))) == -1)
	{
		perror("bind");
		exit(errno);
	}
	else
	{
		printf("Bind address to socket.\n\r");
	}

	addr_len = sizeof(c_addr);
	while(1)
	{
		memset(buff,0,sizeof(buff));
		len = recvfrom(sock,buff,sizeof(buff)-1, 0, (struct sockaddr*)&c_addr, &addr_len);
		if(len<0)
		{
			perror("recvform");
			exit(errno);
		}
		buff[len] = '\0';
		fprintf(stdout,"%d %s\n\r", c_addr.sin_port ,buff);
	}
}


