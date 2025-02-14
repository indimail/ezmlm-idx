/*
 * $Id: hdr_mime.c,v 1.1 2025-01-22 10:52:36+05:30 Cprogrammer Exp mbhangui $
 */
#include "hdr.h"
#include "qmail.h"
#include "makehash.h"
#include "stralloc.h"
#include "str.h"

extern struct qmail qq;
extern char     boundary[HASHLEN];
extern stralloc charset;

/*
 * This list must match enum ctype in hdr.h exactly! 
 */
static const char *ctype_names[] = {
	"text/plain",
	"multipart/mixed",
	"multipart/digest",
	"message/rfc822",
};

void
hdr_ctype(enum ctype ctype)
{
	qmail_puts(&qq, "Content-Type: ");
	qmail_puts(&qq, ctype_names[ctype]);
	switch (ctype) {
	case CTYPE_TEXT:
		/*
		 * text/plain, needs a charset 
		 */
		qmail_puts(&qq, "; charset=");
		qmail_puts(&qq, charset.s);
		break;
	case CTYPE_MULTIPART:
	case CTYPE_DIGEST:
		/*
		 * multipart/something, needs a boundary 
		 */
		qmail_puts(&qq, "; boundary=");
		qmail_put(&qq, boundary, HASHLEN);
		break;
	case CTYPE_MESSAGE:
		break;
	}
	qmail_puts(&qq, "\n");
}

void
hdr_mime(enum ctype ctype)
{
	qmail_puts(&qq, "MIME-Version: 1.0\n");
	hdr_ctype(ctype);
}
/*
 * $Log: hdr_mime.c,v $
 * Revision 1.1  2025-01-22 10:52:36+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
