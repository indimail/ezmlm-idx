#include "strerr.h"
#include "messages.h"
#include "die.h"

no_return void die_usage(void)
{
  strerr_die1x(100,USAGE);
}
