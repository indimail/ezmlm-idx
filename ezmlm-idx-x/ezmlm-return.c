/*
 * $Id: ezmlm-return.c,v 1.1 2025-01-22 10:52:36+05:30 Cprogrammer Exp mbhangui $
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "direntry.h"
#include "stralloc.h"
#include "str.h"
#include "env.h"
#include "sender.h"
#include "sig.h"
#include "strerr.h"
#include "byte.h"
#include "case.h"
#include "open.h"
#include "scan.h"
#include "lockfile.h"
#include "slurpclose.h"
#include "getln.h"
#include "substdio.h"
#include "error.h"
#include "quote.h"
#include "fmt.h"
#include "now.h"
#include "cookie.h"
#include "getconfopt.h"
#include "subdb.h"
#include "messages.h"
#include "die.h"
#include "wrap.h"
#include "config.h"
#include "idx.h"
#include "auto_version.h"

const char      FATAL[] = "ezmlm-return: fatal: ";
const char      INFO[] = "ezmlm-return: info: ";
const char      USAGE[] = "ezmlm-return: usage: ezmlm-return [-dD] dir";

static int      flagdig = 0;

static struct option options[] = {
	OPT_FLAG(flagdig, 'd', 1, 0),
	OPT_FLAG(flagdig, 'D', 0, 0),
	OPT_END
};

static void
die_badretaddr(void)
{
	strerr_die2x(100, FATAL, MSG(ERR_BAD_RETURN_ADDRESS));
}

static void
die_trash(void)
{
	strerr_die2x(99, INFO, "trash address");
}

static char     outbuf[1024];
static substdio ssout;

static char    *hashp = (char *) 0;
static unsigned long addrno = 0L;
static stralloc fndir = { 0 };
static stralloc fndate = { 0 };
static stralloc fndatenew = { 0 };
static stralloc fnhash = { 0 };
static stralloc fnhashnew = { 0 };

static stralloc quoted = { 0 };

static const char *sender;
static const char *workdir;

static void
die_write(const char *fn)
{
	strerr_die2sys(111, FATAL, MSG1(ERR_WRITE, fn));
}

static void
die_hashnew(void)
{
	die_write(fnhashnew.s);
}

static void
die_datenew(void)
{
	die_write(fndatenew.s);
}

static void
die_msgin(void)
{
	strerr_die2sys(111, FATAL, MSG(ERR_READ_INPUT));
}

static void
makedir(const char *s)
{
	if (mkdir(s, 0755) == -1)
		if (errno != error_exist)
			strerr_die2sys(111, FATAL, MSG1(ERR_CREATE, s));
}

static void
dowit(const char *addr, unsigned long when, const stralloc *bounce)
{
	int             fd;
	unsigned int    wpos;
	unsigned long   wdir, wfile;
	char            strnum[FMT_ULONG];

	if (!issub(workdir, addr, 0))
		return;

	if (!stralloc_copys(&fndate, workdir))
		die_nomem();
	if (!stralloc_cats(&fndate, "/bounce/d"))
		die_nomem();
	if (!stralloc_0(&fndate))
		die_nomem();
	fndate.s[fndate.len - 1] = '/';	/* replace '\0' */
	wpos = fndate.len - 1;
	wdir = when / 10000;
	wfile = when - 10000 * wdir;
	if (!stralloc_catb(&fndate, strnum, fmt_ulong(strnum, wdir)))
		die_nomem();
	if (!stralloc_0(&fndate))
		die_nomem();
	makedir(fndate.s);
	--fndate.len; /* remove terminal '\0' */
	if (!stralloc_cats(&fndate, "/w"))
		die_nomem();
	wpos = fndate.len - 1;
	if (!stralloc_catb(&fndate, strnum, fmt_ulong(strnum, wfile)))
		die_nomem();
	if (!stralloc_cats(&fndate, "."))
		die_nomem();
	if (!stralloc_catb(&fndate, strnum, fmt_ulong(strnum, (unsigned long) getpid())))
		die_nomem();
	if (!stralloc_0(&fndate))
		die_nomem();
	if (!stralloc_copy(&fndatenew, &fndate))
		die_nomem();
	fndatenew.s[wpos] = 'W';

	fd = open_trunc(fndatenew.s);
	if (fd == -1)
		die_datenew();
	substdio_fdbuf(&ssout, (ssize_t(*)(int, char *, size_t)) write, fd, outbuf, sizeof (outbuf));
	if (substdio_puts(&ssout, addr) == -1)
		die_datenew();
	if (substdio_put(&ssout, "", 1) == -1)
		die_datenew();
	if (substdio_puts(&ssout, "Return-Path: <") == -1)
		die_datenew();
	if (!quote2(&quoted, sender))
		die_nomem();
	if (substdio_put(&ssout, quoted.s, quoted.len) == -1)
		die_datenew();
	if (substdio_puts(&ssout, ">\n") == -1)
		die_datenew();
	if (substdio_put(&ssout, bounce->s, bounce->len) == -1)
		die_datenew();
	if (substdio_flush(&ssout) == -1)
		die_datenew();
	if (fsync(fd) == -1)
		die_datenew();
	if (close(fd) == -1)
		die_datenew(); /* NFS stupidity */

	wrap_rename(fndatenew.s, fndate.s);
}

static void
doit(const char *addr, unsigned long msgnum, unsigned long when, const stralloc *bounce)
{
	int             fd;
	int             fdnew;
	unsigned int    pos;
	unsigned long   ddir, dfile;
	char            inbuf[1024];
	substdio        ssin;
	char            strnum[FMT_ULONG];
	char            hash[COOKIE];

	if (!issub(workdir, addr, 0))
		return;

	if (!stralloc_copys(&fndate, workdir))
		die_nomem();
	if (!stralloc_cats(&fndate, "/bounce/d"))
		die_nomem();
	if (!stralloc_0(&fndate))
		die_nomem();
	makedir(fndate.s);
	fndate.s[fndate.len - 1] = '/';	/* replace terminal '\0' */
	ddir = when / 10000;
	dfile = when - 10000 * ddir;
	if (!stralloc_catb(&fndate, strnum, fmt_ulong(strnum, ddir)))
		die_nomem();
	if (!stralloc_copy(&fndir, &fndate))
		die_nomem();
	if (!stralloc_0(&fndir))
		die_nomem(); /* make later if necessary (new addr) */
	if (!stralloc_cats(&fndate, "/d"))
		die_nomem();
	pos = fndate.len - 2;
	if (!stralloc_catb(&fndate, strnum, fmt_ulong(strnum, dfile)))
		die_nomem();
	if (!stralloc_cats(&fndate, "."))
		die_nomem();
	if (!stralloc_catb(&fndate, strnum, fmt_ulong(strnum, (unsigned long) getpid())))
		die_nomem();
	if (addrno) { /* so that pre-VERP bounces make a d... file per address */
		/*
		 * for the first one we use the std-style fname 
		 */
		if (!stralloc_cats(&fndate, "."))
			die_nomem();
		if (!stralloc_catb(&fndate, strnum, fmt_ulong(strnum, addrno)))
			die_nomem();
	}
	addrno++; /* get ready for next */
	if (!stralloc_0(&fndate))
		die_nomem();
	if (!stralloc_copy(&fndatenew, &fndate))
		die_nomem();
	fndatenew.s[pos] = '_'; /* fndate = bounce/d/nnnn/dmmmmmm */
	/*
	 * fndatenew = bounce/d/nnnn_dmmmmmm 
	 */

	fd = open_trunc(fndatenew.s);
	if (fd == -1)
		die_datenew();
	substdio_fdbuf(&ssout, (ssize_t(*)(int, char *, size_t)) write, fd, outbuf, sizeof (outbuf));
	if (substdio_puts(&ssout, addr) == -1)
		die_datenew();
	if (substdio_put(&ssout, "", 1) == -1)
		die_datenew();
	if (substdio_puts(&ssout, "Return-Path: <") == -1)
		die_datenew();
	if (!quote2(&quoted, sender))
		die_nomem();
	if (substdio_put(&ssout, quoted.s, quoted.len) == -1)
		die_datenew();
	if (substdio_puts(&ssout, ">\n") == -1)
		die_datenew();
	if (substdio_put(&ssout, bounce->s, bounce->len) == -1)
		die_datenew();
	if (substdio_flush(&ssout) == -1)
		die_datenew();
	if (fsync(fd) == -1)
		die_datenew();
	if (close(fd) == -1)
		die_datenew(); /* NFS stupidity */

	cookie(hash, "", 0, "", addr, "");
	if (!stralloc_copys(&fnhash, workdir))
		die_nomem();
	if (!stralloc_cats(&fnhash, "/bounce/h"))
		die_nomem();
	if (!stralloc_0(&fnhash))
		die_nomem();
	makedir(fnhash.s);
	fnhash.s[fnhash.len - 1] = '/';	/* replace terminal '\0' */
	if (!stralloc_catb(&fnhash, hash, 1))
		die_nomem();
	if (!stralloc_0(&fnhash))
		die_nomem();
	makedir(fnhash.s);
	--fnhash.len; /* remove terminal '\0' */
	if (!stralloc_cats(&fnhash, "/h"))
		die_nomem();
	pos = fnhash.len - 1;
	if (!stralloc_catb(&fnhash, hash + 1, COOKIE - 1))
		die_nomem();
	if (!stralloc_0(&fnhash))
		die_nomem();
	if (!stralloc_copy(&fnhashnew, &fnhash))
		die_nomem();
	fnhashnew.s[pos] = 'H';

	fdnew = open_trunc(fnhashnew.s);
	if (fdnew == -1)
		die_hashnew();
	substdio_fdbuf(&ssout, (ssize_t(*)(int, char *, size_t)) write, fdnew, outbuf, sizeof (outbuf));

	fd = open_read(fnhash.s);
	if (fd == -1) {
		if (errno != error_noent)
			strerr_die2sys(111, FATAL, MSG1(ERR_READ, fnhash.s));
		makedir(fndir.s);
		wrap_rename(fndatenew.s, fndate.s);
	} else {
		substdio_fdbuf(&ssin, (ssize_t(*)(int, char *, size_t)) read, fd, inbuf, sizeof (inbuf));
		switch (substdio_copy(&ssout, &ssin)) {
		case -2:
			die_msgin();
		case -3:
			die_hashnew();
		}
		close(fd);
		if (unlink(fndatenew.s) == -1)
			strerr_die2sys(111, FATAL, MSG1(ERR_DELETE, fndatenew.s));
	}
	if (substdio_puts(&ssout, "   ") == -1)
		die_hashnew();
	if (substdio_put(&ssout, strnum, fmt_ulong(strnum, msgnum)) == -1)
		die_hashnew();
	if (substdio_puts(&ssout, "\n") == -1)
		die_hashnew();
	if (substdio_flush(&ssout) == -1)
		die_hashnew();
	if (fsync(fdnew) == -1)
		die_hashnew();
	if (close(fdnew) == -1)
		die_hashnew(); /* NFS stupidity */

	wrap_rename(fnhashnew.s, fnhash.s);
}

int
main(int argc, char **argv)
{
	char           *action;
	const char     *ret;
	char           *cp;
	unsigned long   msgnum;
	unsigned long   cookiedate;
	unsigned long   when;
	unsigned long   listno = 0L;
	int             match;
	unsigned int    i;
	int             flagmaster = 0;
	int             flagreceipt = 0;
	char            ch;

	stralloc        bounce = { 0 };
	stralloc        line = { 0 };
	stralloc        header = { 0 };
	stralloc        intro = { 0 };
	stralloc        failure = { 0 };
	stralloc        paragraph = { 0 };
	int             flagmasterbounce = 0;
	int             flaghaveheader;
	int             flaghaveintro;

	char            msginbuf[1024];
	substdio        ssmsgin;

	char            strnum[FMT_ULONG];
	char            hash[COOKIE];
	char            hashcopy[COOKIE];

	umask(022);
	sig_pipeignore();
	when = (unsigned long) now();

	getconfopt(argc, argv, options, 1, 0);

	sender = get_sender();
	if (!sender)
		die_sender();
	action = env_get("DEFAULT");
	if (!action)
		strerr_die2x(100, FATAL, MSG(ERR_NODEFAULT));

	initsub(0);

	if (str_start(action, "receipt-")) {
		flagreceipt = 1;
		action += 8;
	}
	ch = *action; /* -d -digest, -m -master, -g -getmaster */
	if (ch && action[1] == '-') {
		switch (ch) {
		case 'g':
			flagmaster = 1;
			flagdig = 1;
			action += 2;
			break;
		case 'm':
			flagmaster = 1;
			action += 2;
			break;
		default:
			break;
		}
	}
	workdir = flagdig ? "digest" : ".";

	if (!*action)
		die_trash();

	if (flagreceipt || flagmaster)	/* check cookie */
		if (str_chr(action, '-') == COOKIE) {
			action[COOKIE] = '\0';
			hashp = action;
			action += COOKIE + 1;
		}

	if (!flagreceipt) {
		if (!flagmaster && str_start(action, "probe-")) {
			action += 6;
			action += scan_ulong(action, &cookiedate);
			if (now() - cookiedate > 3000000)
				die_trash();
			if (*action++ != '.')
				die_trash();
			i = str_chr(action, '-');
			if (i != COOKIE)
				die_trash();
			byte_copy(hashcopy, COOKIE, action);
			action += COOKIE;
			if (*action++ != '-')
				die_trash();
			i = str_rchr(action, '=');
			if (!stralloc_copyb(&line, action, i))
				die_nomem();
			if (action[i]) {
				if (!stralloc_cats(&line, "@"))
					die_nomem();
				if (!stralloc_cats(&line, action + i + 1))
					die_nomem();
			}
			if (!stralloc_0(&line))
				die_nomem();
			strnum[fmt_ulong(strnum, cookiedate)] = 0;
			cookie(hash, key.s, key.len, strnum, line.s, "P");
			if (byte_diff(hash, COOKIE, hashcopy))
				die_trash();

			(void) subscribe(workdir, line.s, 0, "", "-probe", -1);
			_exit(99);
		}

		if (!stralloc_copys(&line, workdir))
			die_nomem();
		if (!stralloc_cats(&line, "/lockbounce"))
			die_nomem();
		if (!stralloc_0(&line))
			die_nomem();

		lockfile(line.s);

		if (!flagmaster && str_start(action, "warn-")) {
			action += 5;
			action += scan_ulong(action, &cookiedate);
			if (now() - cookiedate > 3000000)
				die_trash();
			if (*action++ != '.')
				die_trash();
			i = str_chr(action, '-');
			if (i != COOKIE)
				die_trash();
			byte_copy(hashcopy, COOKIE, action);
			action += COOKIE;
			if (*action++ != '-')
				die_trash();
			i = str_rchr(action, '=');
			if (!stralloc_copyb(&line, action, i))
				die_nomem();
			if (action[i]) {
				if (!stralloc_cats(&line, "@"))
					die_nomem();
				if (!stralloc_cats(&line, action + i + 1))
					die_nomem();
			}
			if (!stralloc_0(&line))
				die_nomem();
			strnum[fmt_ulong(strnum, cookiedate)] = 0;
			cookie(hash, key.s, key.len, strnum, line.s, "W");
			if (byte_diff(hash, COOKIE, hashcopy))
				die_trash();

			if (slurpclose(0, &bounce, 1024) == -1)
				die_msgin();
			dowit(line.s, when, &bounce);
			_exit(99);
		}
	}
	action += scan_ulong(action, &msgnum);
	if (*action++ != '-')
		die_badretaddr();
	cp = action;
	if (*action >= '0' && *action <= '9') {	/* listno */
		action += scan_ulong(action, &listno);
		listno++; /* logging is 1-53, not 0-52 */
	}

	if (hashp) { /* scrap bad cookies */
		if ((ret = checktag(msgnum, 0L, "x", (char *) 0, hashp))) {
			if (*ret)
				strerr_die2x(111, FATAL, ret);
			else
				die_trash();
		} else
		if (flagreceipt) {
			if (!(ret = logmsg(msgnum, listno, 0L, 5))) {
				closesub();
				strerr_die6x(99, INFO, "receipt:", cp, " [", hashp, "]");
			}
			if (*ret)
				strerr_die2x(111, FATAL, ret);
			else
				strerr_die2x(0, INFO, MSG(ERR_DONE));
		} else
		if (*action) {	/* post VERP master bounce */
			if ((ret = logmsg(msgnum, listno, 0L, -1))) {
				closesub();
				strerr_die4x(0, INFO, "bounce [", hashp, "]");
			}
			if (*ret)
				strerr_die2x(111, FATAL, ret);
			else
				strerr_die2x(99, INFO, MSG(ERR_DONE));
		}
	} else
	if (flagreceipt || flagmaster)
		die_badretaddr();

	if (*action) {
		i = str_rchr(action, '=');
		if (!stralloc_copyb(&line, action, i))
			die_nomem();
		if (action[i]) {
			if (!stralloc_cats(&line, "@"))
				die_nomem();
			if (!stralloc_cats(&line, action + i + 1))
				die_nomem();
		}
		if (!stralloc_0(&line))
			die_nomem();
		if (slurpclose(0, &bounce, 1024) == -1)
			die_msgin();
		doit(line.s, msgnum, when, &bounce);
		_exit(99);
	}

	/*
	 * pre-VERP bounce, in QSBMF format. Receipts are never pre-VERP 
	 */

	substdio_fdbuf(&ssmsgin, (ssize_t(*)(int, char *, size_t)) read, 0, msginbuf, sizeof (msginbuf));

	flaghaveheader = 0;
	flaghaveintro = 0;

	for (;;) {
		if (!stralloc_copys(&paragraph, ""))
			die_nomem();
		for (;;) {
			if (getln(&ssmsgin, &line, &match, '\n') == -1)
				die_msgin();
			if (!match)
				die_trash();
			if (!stralloc_cat(&paragraph, &line))
				die_nomem();
			if (line.len <= 1)
				break;
		}

		if (!flaghaveheader) {
			if (!stralloc_copy(&header, &paragraph))
				die_nomem();
			flaghaveheader = 1;
			continue;
		}

		if (!flaghaveintro) {
			if (paragraph.s[0] == '-' && paragraph.s[1] == '-')
				continue; /* skip MIME boundary if it exists */
			if (paragraph.len < 15)
				die_trash();
			if (str_diffn(paragraph.s, "Hi. This is the", 15))
				die_trash();
			if (!stralloc_copy(&intro, &paragraph))
				die_nomem();
			flaghaveintro = 1;
			continue;
		}

		if (paragraph.s[0] == '-')
			break;

		if (paragraph.s[0] == '<') {
			if (!stralloc_copy(&failure, &paragraph))
				die_nomem();

			if (!stralloc_copy(&bounce, &header))
				die_nomem();
			if (!stralloc_cat(&bounce, &intro))
				die_nomem();
			if (!stralloc_cat(&bounce, &failure))
				die_nomem();

			i = byte_chr(failure.s, failure.len, '\n');
			if (i < 3)
				die_trash();

			if (!stralloc_copyb(&line, failure.s + 1, i - 3))
				die_nomem();
			if (byte_chr(line.s, line.len, '\0') == line.len) {
				if (!stralloc_0(&line))
					die_nomem();
				if (flagmaster) { /* bounced msg slave! */
					if ((i = str_rchr(line.s, '@')) >= 5) { /* 00_52@host */
						line.s[i] = '\0'; /* 00_52 */
						(void) scan_ulong(line.s + i - 5, &listno);
						if ((ret = logmsg(msgnum, listno + 1, 0L, -1)) && *ret)
							strerr_die2x(111, FATAL, ret);
						strerr_warn3(INFO, "bounce ", line.s + i - 5, (struct strerr *) 0);
						flagmasterbounce = 1;
					}
				} else
					doit(line.s, msgnum, when, &bounce);
			}
		}
	}
	closesub();
	if (flagmasterbounce)
		strerr_die3x(0, "[", hashp, "]");
	else
		_exit(99);
	(void) argc;
}
/*
 * $Log: ezmlm-return.c,v $
 * Revision 1.1  2025-01-22 10:52:36+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
