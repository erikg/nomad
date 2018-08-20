#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "net.h"

int
net_listen(int port, void (*callback)(unsigned char *)) {
	struct sockaddr_in addr;
	unsigned char buf[1024];
	int sock;

	memset((void *)&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("failed to bind");
		return -1;
	}

	printf("Go time\n");
	while (1) {
		int len = 0;
		memset(buf,0,5);
		len = recvfrom(sock, buf, 1024, 0, NULL, 0);
		if (len < 0) {
			printf("Uhhh?\n");
			close(sock);
			return -1;
		} else if (len > 0) {
			if(!strncmp((const char *)buf,"QUIT",4)) {
				close(sock);
				return 0;
			}	
			callback(buf);
		} else {
			printf("Nothing\n");
		}
	}
}
