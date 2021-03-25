# ezmlm-idx

Easy Mailing List Manager for [indimail-mta](https://github.com/mbhangui/indimail-mta), [qmail](https://cr.yp.to/qmail.html)

This has been forked from [ezmlm-idx Project Homepage](https://untroubled.org/ezmlm/) to adapt it to work with indimail-mta's multi-queue architecture.

ezmlm is an easy-to-use, high-speed mailing list manager for qmail.

ezmlm lets users set up their own mailing lists within qmail's address hierarchy. A user, Joe, types `ezmlm-make ~/SOS ~/.qmail-sos joe-sos isp.net` and instantly has a functioning mailing list, joe-sos@isp.net, with all relevant information stored in a new ~/SOS directory.

ezmlm sets up joe-sos-subscribe and joe-sos-unsubscribe for automatic processing of subscription and unsubscription requests. Any message to joe-sos-subscribe will work; Joe doesn't have to explain any tricky command formats. ezmlm will send back instructions if a subscriber sends a message to joe-sos-request or joe-sos-help.

ezmlm automatically archives new messages. Messages are labelled with sequence numbers; a subscriber can fetch message 123 by sending mail to joe-sos-get.123. The archive format supports fast message retrieval even when there are thousands of messages.

ezmlm takes advantage of qmail's VERPs to reliably determine the recipient address and message number for every incoming bounce message. It waits ten days and then sends the subscriber a list of message numbers that bounced. If that warning bounces, ezmlm sends a probe; if the probe bounces, ezmlm automatically removes the subscriber from the mailing list.

ezmlm is easy for users to control. Joe can edit ~/SOS/text/\* to change any of the administrative messages sent to subscribers. He can remove ~/SOS/public and ~/SOS/archived to disable automatic subscription and archiving. He can put his own address into ~/SOS/editor to set up a moderated mailing list. He can edit ~/SOS/{headeradd,headerremove} to control outgoing headers. ezmlm has several utilities to manually inspect and manage mailing lists.

ezmlm uses `Delivered-To` header to stop forwarding loops, Mailing-List to protect other mailing lists against false subscription requests, and real cryptographic cookies to protect normal users against false subscription requests. ezmlm can also be used for a sublist, redistributing messages from another list.

ezmlm is reliable, even in the face of system crashes. It writes each ew subscription and each new message safely to disk before it reports success to [indimail-mta](https://github.com/mbhangui/indimail-mta).

ezmlm doesn't mind huge mailing lists. Lists don't even have to fit into emory. ezmlm hashes the subscription list into a set of independent files so that it can handle subscription requests quickly. ezmlm uses mail for blazingly fast parallel SMTP deliveries.

ezmlm-idx originated as an add-on to [ezmlm](https://cr.yp.to/ezmlm.html). It now exists as a complete package on its own, but can still be considered essentially as an extension to ezmlm. It adds multi-message threaded message retrieval from the archive, digests, message and subscription moderation, and a number of remote administration function. It modifies the configuration program ezmlm-make(1) so that it uses a text file template rather than compiled-in texts in list creation. In this manner, ezmlm-idx allows easy setup of lists in different languages and customization of default list setup. ezmlm-idx also adds MIME handling, and other support to streamline use with languages other than English. Prior to version 7, ezmlm-idx existed as an ezmlm source add-on, and as such did not work without ezmlm. ezmlm-idx tries to be compatible with ezmlm as much as possible in its usage, though the internal structure has changed considerably. ezmlm-idx also modifies the ezmlm subscriber database to be case insensitive to avoid many unsubscribe problems.

# Source Compiling/Linking

## Download / clone / compile libqmail

[![ezmlm-idx Ubuntu, Mac OSX CI](https://github.com/mbhangui/ezmlm-idx/actions/workflows/ezmlm-idx-c-cpp.yml/badge.svg)](https://github.com/mbhangui/ezmlm-idx/actions/workflows/ezmlm-idx-c-cpp.yml)
[![ezmlm-idx FreeBSD CI](https://github.com/mbhangui/ezmlm-idx/actions/workflows/ezmlm-idx-freebsd.yml/badge.svg)](https://github.com/mbhangui/ezmlm-idx/actions/workflows/ezmlm-idx-freebsd.yml)

ezmlm-idx uses functions from libqmail library. libqmail uses GNU autotools. You need to haave autoconf, automake, libtool and pkg config package. Follow the instructions below to have them installed in case you don't have them.

```
$ cd /usr/local/src
$ git clone https://github.com/mbhangui/libqmail.git
$ cd /usr/local/src/libqmail
$ ./default.configure
$ make
$ sudo make install-strip
```

(check version in libqmail/conf-version)

NOTE: for FreeBSD, install packages using pkg

```
# pkg install automake autoconf libtool pkgconf
```

NOTE: For Darwin (Mac OSX), install [MacPorts](https://www.macports.org/) or brew. You can look at this [document](https://paolozaino.wordpress.com/2015/05/05/how-to-install-and-use-autotools-on-mac-os-x/) for installing MacPorts.

```
# port install autoconf libtool automake pkgconfig
# port install openssl
# port update outdated
```

## Download / clone / compile ezmlm-idx

```
$ cd /usr/local/src
$ git clone https://github.com/mbhangui/ezmlm-idx.git
$ cd /usr/local/src/ezmlm-idx/ezmlm-idx-x
$ ./default.configure
$ make
$ sudo make install-strip
```

# Binary Builds on openSUSE Build Service

**Build Status on [Open Build Service](https://build.opensuse.org/project/show/home:mbhangui)**

[![ezmlm-idx obs trigger](https://github.com/mbhangui/ezmlm-idx/actions/workflows/ezmlm-idx-obs.yml/badge.svg)](https://github.com/mbhangui/ezmlm-idx/actions/workflows/ezmlm-idx-obs.yml)

You can get binary RPM / Debian packages at

* [Stable Releases](http://download.opensuse.org/repositories/home:/indimail/)
* [Experimental Releases](http://download.opensuse.org/repositories/home:/mbhangui/)

If you want to use DNF / YUM / apt-get, the corresponding install instructions for the two repositories, depending on whether you want to install a stable or an experimental release, are

* [Stable](https://software.opensuse.org/download.html?project=home%3Aindimail&package=ezmlm-idx)
* [Experimental](https://software.opensuse.org/download.html?project=home%3Ambhangui&package=ezmlm-idx)

```
Currently, the list of supported distributions for ezmlm-idx is

    * SUSE
          o openSUSE_Leap_15.0
          o openSUSE_Leap_15.1
          o openSUSE_Leap_15.2
          o openSUSE_Tumbleweed
          o SUSE Linux Enterprise 12
          o SUSE Linux Enterprise 12 SP1
          o SUSE Linux Enterprise 12 SP2
          o SUSE Linux Enterprise 12 SP3
          o SUSE Linux Enterprise 12 SP4
          o SUSE Linux Enterprise 12 SP5
          o SUSE Linux Enterprise 15
          o SUSE Linux Enterprise 15 SP1

    * Red Hat
          o Fedora 32
          o Fedora 33
          o Red Hat Enterprise Linux 7
          o CentOS 7
          o CentOS 8

    * Debian
          o Debian  9.0
          o Debian 10.0

    * Ubuntu
          o Ubuntu 16.04
          o Ubuntu 17.04
          o Ubuntu 18.04
          o Ubuntu 19.04
          o Ubuntu 19.10
          o Ubuntu 20.04
          o Ubuntu 20.10
```

# SUPPORT INFORMATION

For this forked version of ezmlm-idx, you can contact on IRC or mailing list

## IRC / Matrix

![Matrix](https://img.shields.io/matrix/indimail:matrix.org)

* Join me [#indimail:matrix.org](https://matrix.to/#/#indimail:matrix.org)
* IndiMail has an IRC channel #indimail-mta

## Mailing list

There are four Mailing Lists for IndiMail

1. indimail-support  - You can subscribe for Support [here](https://lists.sourceforge.net/lists/listinfo/indimail-support). You can mail [indimail-support](mailto:indimail-support@lists.sourceforge.net) for support Old discussions can be seen [here](https://sourceforge.net/mailarchive/forum.php?forum_name=indimail-support)
2. indimail-devel - You can subscribe [here](https://lists.sourceforge.net/lists/listinfo/indimail-devel). You can mail [indimail-devel](mailto:indimail-devel@lists.sourceforge.net) for development activities. Old discussions can be seen [here](https://sourceforge.net/mailarchive/forum.php?forum_name=indimail-devel)
3. indimail-announce - This is only meant for announcement of New Releases or patches. You can subscribe [here](http://groups.google.com/group/indimail)
4. Archive at [Google Groups](http://groups.google.com/group/indimail). This groups acts as a remote archive for indimail-support and indimail-devel.

There is also a [Project Tracker](http://sourceforge.net/tracker/?group_id=230686) for IndiMail (Bugs, Feature Requests, Patches, Support Requests)

## CREDITS

The IDX patches add: Indexing, (Remote) Moderation, digest, make patches, multi-language, MIME, global interface, SQL database support.

Fred Lindberg <lindberg@id.wustl.edu>, Fred B. Ringel <fredr@rivertown.net>, Bruce Guenter <bruce@untroubled.org>, and many others
