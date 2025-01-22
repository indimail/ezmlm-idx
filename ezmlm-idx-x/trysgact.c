/*
 * $Idx: $
 *
 * Public domain, from daemontools-0.76. 
 */

#include <signal.h>

main()
{
	struct sigaction sa;
	sa.sa_handler = 0;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(0, &sa, (struct sigaction *) 0);
}
/*
 * $Log: trysgact.c,v $
 * Revision 1.1  2025-01-22 10:52:37+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
