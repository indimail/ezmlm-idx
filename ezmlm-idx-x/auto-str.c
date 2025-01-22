/*
 * $Id: auto-str.c,v 1.1 2025-01-22 10:52:39+05:30 Cprogrammer Exp mbhangui $
 */
#include <unistd.h>
#include <ctype.h>
#include "str.h"
#include "subfd.h"
#include "substdio.h"

/*
 * check if a given character can be printed unquoted in a C string
 * does not accept digits as they may be hardly visible between octal
 * encoded chars
 */
static int
is_legible(unsigned char ch)
{
	if (isascii(ch))
		return 1;
	if (ch == '/' || ch == '_' || ch == '-' || ch == '.')
		return 1;
	return 0;
}

void
subputs(const char *s)
{
	if (substdio_puts(subfdout, s) == -1)
		_exit(111);
}

void
subputsbin(const char *s)
{
	char            octal[5];
	unsigned char   ch;
	while ((ch = *s++) != 0) {
		if (is_legible(ch)) {
			if (substdio_put(subfdout, (char *) &ch, 1) == -1)
				_exit(111);
		} else {
			octal[4] = 0;
			octal[3] = '0' + (ch & 7);
			ch >>= 3;
			octal[2] = '0' + (ch & 7);
			ch >>= 3;
			octal[1] = '0' + (ch & 7);
			octal[0] = '\\';
			subputs(octal);
		}
	}
}

int
main(int argc, char **argv)
{
	char           *name;
	char           *env;
	char            value[256];
	int             len;

	name = argv[1];
	if (!name)
		_exit(100);
	env = argv[2];
	if ((len = substdio_get(subfdin, value, sizeof value - 1)) <= 0)
		_exit(100);
	value[len] = 0;
	value[str_chr(value, '\n')] = 0;

	if (env) {
		subputs("#include \"env.h\"\n" "const char *");
		subputs(name);
		subputs("(void)\n" "{\n" "  static const char *env = 0;\n" "  if (env == 0)\n" "    if ((env = env_get(\"");
		subputs(env);
		subputs("\")) == 0)\n" "      env = \"");
		subputsbin(value);
		subputs("\";\n" "  return env;\n" "}\n");
	} else {
		subputs("const char ");
		subputs(name);
		subputs("[] = \"");
		subputsbin(value);
		subputs("\";\n");
	}
	if (substdio_flush(subfdout) == -1)
		_exit(111);
	return 0;
	(void) argc;
}
/*
 * $Log: auto-str.c,v $
 * Revision 1.1  2025-01-22 10:52:39+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
