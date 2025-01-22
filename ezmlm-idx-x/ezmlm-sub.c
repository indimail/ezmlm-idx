/*
 * $Id: ezmlm-sub.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
const char      FATAL[] = "ezmlm-sub: fatal: ";
const char      USAGE[] = "ezmlm-sub: usage: ezmlm-sub [-HmMnNvV] [-h hash] [-t tag] dir [subdir] [box@domain [name]] ...";

extern void     subunsub_main(int submode, int argc, char **argv) __attribute__ ((noreturn));

int
main(int argc, char **argv)
{
	subunsub_main(1, argc, argv);
}
/*
 * $Log: ezmlm-sub.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
