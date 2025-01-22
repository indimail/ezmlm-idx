/*
 * $Id: ezmlm-unsub.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
const char      FATAL[] = "ezmlm-unsub: fatal: ";
const char      USAGE[] = "ezmlm-unsub: usage: ezmlm-unsub [-HmMnNvV] [-h hash] [-t tag] dir [subdir] [box@domain ...]";

extern void     subunsub_main(int submode, int argc, char **argv) __attribute__ ((noreturn));

int
main(int argc, char **argv)
{
	subunsub_main(0, argc, argv);
}
/*
 * $Log: ezmlm-unsub.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
