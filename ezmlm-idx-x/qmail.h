#ifndef QMAIL_H
#define QMAIL_H

#include "substdio.h"
#include "stralloc.h"

#define CUSTOM_ERR_FD 2
struct qmail {
  int flagerr;
  long pid;
  unsigned long msgbytes;
  int fdm;
  int fde;
  int fdc;
  substdio ss;
  char buf[1024];
} ;

extern int qmail_open(struct qmail *);
extern void qmail_put(struct qmail *, const char *, int);
extern void qmail_puts(struct qmail *, const char *);
extern void qmail_from(struct qmail *, const char *);
extern void qmail_to(struct qmail *, const char *);
extern void qmail_fail(struct qmail *);
extern const char *qmail_close(struct qmail *);
extern unsigned long qmail_qp(struct qmail *);
extern int qmail_copy(struct qmail *, substdio *,long);

#endif
