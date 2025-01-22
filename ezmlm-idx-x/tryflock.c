/*
 * $Idx: $
 *
 * Public domain, from daemontools-0.76. 
 */

#include <sys/types.h>
#include <sys/file.h>
#include <fcntl.h>

main()
{
	flock(0, LOCK_EX | LOCK_UN | LOCK_NB);
}
/*
 * $Log: tryflock.c,v $
 * Revision 1.1  2025-01-22 10:52:37+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
