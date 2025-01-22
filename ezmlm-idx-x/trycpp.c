/*
 * $Idx: $
 *
 * Public domain, from daemontools-0.76. 
 */

int
main()
{
#ifdef NeXT
	printf("nextstep\n");
	exit(0);
#endif
	printf("unknown\n");
	exit(0);
}
/*
 * $Log: trycpp.c,v $
 * Revision 1.1  2025-01-22 10:52:37+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
