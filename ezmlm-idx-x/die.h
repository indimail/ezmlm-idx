#ifndef DIE_H
#define DIE_H
#include <noreturn.h>

extern const char FATAL[];
extern const char USAGE[];

extern no_return void die_badaddr(void);
extern no_return void die_badformat(void);
extern no_return void die_dow(void);
extern no_return void die_nomem(void);
extern no_return void die_sender(void);
extern no_return void die_usage(void);

#endif
