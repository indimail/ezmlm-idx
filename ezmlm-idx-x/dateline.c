/*
 * $Id: dateline.c,v 1.1 2025-01-22 10:52:39+05:30 Cprogrammer Exp mbhangui $
 */
#include "fmt.h"
#include "yyyymm.h"
#include "stralloc.h"
#include "cgi.h"

/*- converts yyyymm from unsigned long d to text dt */
int
dateline(stralloc *dt, unsigned long d)
{
	char            strnum[FMT_ULONG];
	const char     *mo;
	switch (d % 100) {
	case 1:
		mo = "January";
		break;
	case 2:
		mo = "February";
		break;
	case 3:
		mo = "March";
		break;
	case 4:
		mo = "April";
		break;
	case 5:
		mo = "May";
		break;
	case 6:
		mo = "June";
		break;
	case 7:
		mo = "July";
		break;
	case 8:
		mo = "August";
		break;
	case 9:
		mo = "September";
		break;
	case 10:
		mo = "October";
		break;
	case 11:
		mo = "November";
		break;
	case 12:
		mo = "December";
		break;
	case 0:
		mo = "????";
		break;
	default:
		cgierr("I don't know any month > 12", "", "");
	}
	if (!stralloc_copys(dt, mo))
		return -1;
	if (!stralloc_cats(dt, " "))
		return -1;
	if ((d / 100)) {
		if (!stralloc_catb(dt, strnum, fmt_ulong(strnum, d / 100)))
			return -1;
	} else
	if (!stralloc_cats(dt, "????"))
		return 0;
	return 1;
}
/*
 * $Log: dateline.c,v $
 * Revision 1.1  2025-01-22 10:52:39+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
