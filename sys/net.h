#ifndef NET_H
#define NET_H

int net_listen(int socket, void (*)(unsigned char *data));

#endif
