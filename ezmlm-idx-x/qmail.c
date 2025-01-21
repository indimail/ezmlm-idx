#include <unistd.h>
#include "substdio.h"
#include "wait.h"
#include "env.h"
#include "str.h"
#include "scan.h"
#include "fd.h"
#include "error.h"
#include "stralloc.h"
#include "envdir.h"
#include "pathexec.h"
#include "qmail.h"
#include "auto_etc.h"

static stralloc tmp = { 0 };

int qmail_open(struct qmail *qq)
{
  int pim[2], pie[2];
  int pic[2], i, unreadable = 0, errfd; /*- custom message */
  const char *etc_dir;
  const char *x, *err, *ezmlm_etc, *ezmlm_queue, *qmail_queue;
  char *binqqargs[2] = { 0, 0 };
  char **e, **orig_env;
  char errbuf[256];
  substdio sserr;

  qq->msgbytes = 0L;
  if (pipe(pim) == -1) return -1;
  if (pipe(pie) == -1) { close(pim[0]); close(pim[1]); return -1; }
  if (pipe(pic) == -1) { close(pim[0]); close(pim[1]); close(pie[0]); close(pie[1]); return -1; }

  switch(qq->pid = fork()) {
    case -1:
      close(pim[0]); close(pim[1]);
      close(pie[0]); close(pie[1]);
      close(pic[0]); close(pic[1]);
      return -1;
    case 0:
      close(pim[1]);
      close(pie[1]);
      close(pic[0]); /*- we want to receive data */
      if (fd_move(0,pim[0]) == -1) _exit(120);
      if (fd_move(1,pie[0]) == -1) _exit(120);
      if (!(x = env_get("ERROR_FD"))) errfd = CUSTOM_ERR_FD;
      else scan_int(x, &errfd);
      if (fd_move(errfd, pic[1]) == -1) _exit(120);
      if (chdir("/") == -1) _exit(120);
      ezmlm_etc = env_get("EZMLM_ETC");
      ezmlm_queue = env_get("EZMLMQUEUE");
      qmail_queue = env_get("QMAILQUEUE");
      etc_dir = auto_etc();
      if (!stralloc_copys(&tmp, etc_dir) ||
          !stralloc_catb(&tmp, "/global_vars", 12) ||
          !stralloc_0(&tmp))
        _exit(51);
      if (!access(tmp.s, X_OK)) {
        orig_env = environ;
        env_clear();
        if ((i = envdir((char *) tmp.s, &err, 1, &unreadable))) {
          substdio_fdbuf(&sserr,(ssize_t (*) (int, char *, size_t)) write,errfd,errbuf,sizeof(errbuf));
          substdio_put(&sserr, "Zenvdir: ", 9);
          substdio_puts(&sserr, envdir_str(i));
          substdio_put(&sserr, ": ", 2);
          substdio_puts(&sserr, err);
          substdio_put(&sserr, " (#4.3.0)", 9);
          substdio_flush(&sserr);
          _exit(88);
        }
        if ((e = pathexec(0))) {
          environ = e;
          if (!env_get("EZMLM_ETC") && ezmlm_etc && !env_put2("EZMLM_ETC", ezmlm_etc))
            _exit(51);
          if (!env_get("EZMLMQUEUE") && ezmlm_queue && !env_put2("EZMLMQUEUE", ezmlm_queue))
            _exit(51);
          if (!env_get("QMAILQUEUE") && qmail_queue && !env_put2("QMAILQUEUE", qmail_queue))
            _exit(51);
        } else
          environ = orig_env;
      } else
      if (errno != error_noent)
          _exit(55);
      if (!binqqargs[0]) binqqargs[0] = env_get("EZMLMQUEUE");
      if (!binqqargs[0]) binqqargs[0] = env_get("QMAILQUEUE");
      if (!binqqargs[0]) binqqargs[0] = "sbin/ezmlm-queue";
      execv(*binqqargs,binqqargs);
      _exit(120);
  }

  qq->fdm = pim[1]; close(pim[0]);
  qq->fde = pie[1]; close(pie[0]);
  qq->fdc = pic[0]; close(pic[1]);
  substdio_fdbuf(&qq->ss,(ssize_t (*) (int, char *, size_t)) write,qq->fdm,qq->buf,sizeof(qq->buf));
  qq->flagerr = 0;
  return 0;
}

unsigned long qmail_qp(struct qmail *qq)
{
  return qq->pid;
}

void qmail_fail(struct qmail *qq)
{
  qq->flagerr = 1;
}

void qmail_put(struct qmail *qq, const char *s, int len)
{
  if (!qq->flagerr && substdio_put(&qq->ss,s,len) == -1) qq->flagerr = 1;
  qq->msgbytes += len;
}

void qmail_puts(struct qmail *qq, const char *s)
{
  int len;
  len = str_len(s);
  if (!qq->flagerr && substdio_put(&qq->ss,s,len) == -1) qq->flagerr = 1;
  qq->msgbytes += len;
}

void qmail_from(struct qmail *qq, const char *s)
{
  if (substdio_flush(&qq->ss) == -1) qq->flagerr = 1;
  close(qq->fdm);
  substdio_fdbuf(&qq->ss,(ssize_t (*) (int, char *, size_t)) write,qq->fde,qq->buf,sizeof(qq->buf));
  qmail_put(qq,"F",1);
  qmail_puts(qq,s);
  qmail_put(qq,"",1);
}

void qmail_to(struct qmail *qq, const char *s)
{
  qmail_put(qq,"T",1);
  qmail_puts(qq,s);
  qmail_put(qq,"",1);
}

const char     *
qmail_close(struct qmail *qq)
{
  int             wstat, exitcode, len = 0;
  char            ch;
  static char     errstr[1024];

  qmail_put(qq, "", 1);
  if (!qq->flagerr && substdio_flush(&qq->ss) == -1)
    qq->flagerr = 1;
  close(qq->fde);
  substdio_fdbuf(&qq->ss, (ssize_t (*) (int, char *, size_t)) read, qq->fdc, qq->buf, sizeof(qq->buf));
  while (substdio_bget(&qq->ss, &ch, 1) && len < (sizeof(errstr) - 1)) {
    errstr[len] = ch;
    len++;
  }
  if (len > 0)
    errstr[len] = 0; /*- terminate errstr */
  close(qq->fdc);
  if (wait_pid(&wstat, qq->pid) != qq->pid)
    return "Zqq waitpid surprise (#4.3.0)";
  if (wait_crashed(wstat))
    return "Zqq crashed (#4.3.0)";
  exitcode = wait_exitcode(wstat);
  switch (exitcode)
  {
  case 115: /*- compatibility */
  case 11:
    return "Denvelope address too long for qq (#5.1.3)";
  case 31:
    return "Dmail server permanently rejected message (#5.3.0)";
  case 32: /*-*/
    return "DSPAM or junk mail threshold exceeded (#5.7.1)";
  case 33: /*-*/
    return "DMessage contains virus (#5.7.1)";
  case 34: /*-*/
    return "DMessage contains banned attachment (#5.7.1)";
  case 35: /*-*/
    return "DPrivate key file does not exist (#5.3.5)";
  case 50: /*-*/
    return "Zunable to set uid/gid (#4.3.0)";
  case 51:
    return "Zqq out of memory (#4.3.0)";
  case 52:
    return "Zqq timeout (#4.3.0)";
  case 53:
    return "Zqq write error or disk full (#4.3.0)";
  case 0:
    if (!qq->flagerr)
      return "";
    /*- fall through */
  case 54:
    return "Zqq read error (#4.3.0)";
  case 55:
    return "Zqq unable to read configuration (#4.3.0)";
  case 56:
    return "Zqq trouble making network connection (#4.3.0)";
  case 57: /*-*/
    return "Zunable to open shared object/plugin (#4.3.0)";
  case 58: /*-*/
    return "Zunable to resolve symbol in shared object/plugin (#4.3.0)";
  case 59: /*-*/
    return "Zunable to close shared object/plugin (#4.3.0)";
  case 60: /*-*/
    return "Zqq trouble creating pipes/sockets (#4.3.0)";
  case 61:
    return "Zqq trouble in home directory (#4.3.0)";
  case 62: /*-*/
    return "Zqq unable to access mess file (#4.3.0)";
  case 63:
  case 64:
  case 65:
  case 66:
    return "Zqq trouble creating files in queue (#4.3.0)";
  case 67: /*-*/
    return "Zqq trouble getting uids/gids (#4.3.0)";
  case 68: /*-*/
    return "Zqq trouble creating temporary files (#4.3.0)";
  case 71:
    return "Zmail server temporarily rejected message (#4.3.0)";
  case 72:
    return "Zconnection to mail server timed out (#4.4.1)";
  case 73:
    return "Zconnection to mail server rejected (#4.4.1)";
  case 74:
    return "Zcommunication with mail server failed (#4.4.2)";
  case 75: /*-*/
    return "Zunable to exec (#4.3.0)";
  case 76: /*-*/
    return "Ztemporary problem with SPAM filter (#4.3.0)";
  case 77: /*- thanks to problem repoted by peter cheng */
    return "Zqq unable to run QHPSI scanner (#4.3.0)";
  case 79:
    return "Zqq Envelope format error (#4.3.0)";
  case 91:
    /*- fall through */
  case 81:
    return "Zqq internal bug (#4.3.0)";
  case 87: /*-*/
    return "Zmail system incorrectly configured. (#4.3.5)";
  case 82: /*- compatability with simscan, notqmail, etc */
  case 88: /*- custom error */
    if (len > 2)
      return errstr;
  case 120:
    return "Zunable to exec qq (#4.3.0)";
  case 121: /*-*/
    return "Zunable to fork (#4.3.0)";
  case 122: /*-*/
    return "Zqq waitpid surprise (#4.3.0)";
  case 123: /*-*/
    return "Zqq crashed (#4.3.0)";
  default:
    if ((exitcode >= 11) && (exitcode <= 40))
      return "Dqq permanent problem (#5.3.0)";
    return "Zqq temporary problem (#4.3.0)";
  }
}
