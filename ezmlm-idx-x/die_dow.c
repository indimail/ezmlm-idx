#include "strerr.h"
#include "messages.h"
#include "die.h"

no_return void die_dow(void)
{
  strerr_die2x(100,FATAL,MSG(ERR_DOW));
}
