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
	struct sockaddr_in s_addr;
	int sock;
	int addr_len;
	int len;
	char buff[128] = "Hello IP 222.71.233.159";
	if( (sock=socket(AF_INET,SOCK_DGRAM,0)) == -1)
	{
		perror("socket");
		exit(errno);
	}
	else
		fprintf(stdout,"create socket.\n\r");

	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(6660);
	s_addr.sin_addr.s_addr =inet_addr("222.71.233.159");
	
	addr_len = sizeof(s_addr);
	len = sendto(sock,buff,strlen(buff),0,(struct sockaddr *)&s_addr, addr_len);
	if(len < 0)
	{
		fprintf(stdout, "send error.\n\\r");
		return 3;
	}
	fprintf(stdout, "Send success.\n\r");
}
