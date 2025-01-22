/*
 * $Idx: $
 *
 * Public domain, from daemontools-0.76. 
 */

#include <sys/types.h>
#include <sys/wait.h>

main()
{
	waitpid(0, 0, 0);
}
/*
 * $Log: trywaitp.c,v $
 * Revision 1.1  2025-01-22 10:52:37+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
