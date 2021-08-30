#include <unistd.h>
#include "strerr.h"
#include "messages.h"
#include "die.h"

no_return void die_badaddr(void)
{
  strerr_die2x(100,FATAL,MSG(ERR_BAD_ADDRESS));
  _exit(100);
}
