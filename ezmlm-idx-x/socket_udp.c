/*
 * $Idx: $
 *
 * Public domain, from djbdns-1.05. 
 */

#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "ndelay.h"
#include "socket.h"

int
socket_udp(void)
{
	int             s;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == -1)
		return -1;
	if (ndelay_on(s) == -1) {
		close(s);
		return -1;
	}
	return s;
}
/*
 * $Log: socket_udp.c,v $
 * Revision 1.1  2025-01-22 10:52:37+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
