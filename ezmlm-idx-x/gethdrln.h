#ifndef _GETHDRLN_H
#define _GETHDRLN_H
#include <substdio.h>
#include <stralloc.h>

extern int gethdrln(struct substdio *ss, struct stralloc *sa, int *match, int sep);
extern int getln2_idx(substdio *, stralloc *, char **, unsigned int *, int);
#endif
