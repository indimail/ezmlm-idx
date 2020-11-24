#ifndef _GETHDRLN_H
#define _GETHDRLN_H
#include <substdio.h>
#include <stralloc.h>

extern int gethdrln(struct substdio *ss, struct stralloc *sa, int *match, int sep);
#endif
