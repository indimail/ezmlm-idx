# ezmlm-idx

Easy Mailing List Manager for [indimail-mta](https://github.com/mbhangui/indimail-mta), [qmail](https://cr.yp.to/qmail.html)

This has been forked from [ezmlm-idx Project Homepage](https://untroubled.org/ezmlm/) to adapt it to work with indimail-mta's muti-queues architecture.

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

## CREDITS

The IDX patches add: Indexing, (Remote) Moderation, digest, make Fred Lindberg <lindberg@id.wustl.edu>, Fred B. Ringel <fredr@rivertown.net>, Bruce Guenter <bruce@untroubled.org>, and many others

# SUPPORT INFORMATION

ezmlm-idx is supported at IndiMail

## IRC / Matrix

* Join me https://matrix.to/#/#indimail:matrix.org
* IndiMail has an IRC channel #indimail-mta

## Mailing list

There are four Mailing Lists for IndiMail

1. indimail-support  - You can subscribe for Support [here](https://lists.sourceforge.net/lists/listinfo/indimail-support). You can mail [indimail-support](mailto:indimail-support@lists.sourceforge.net) for support Old discussions can be seen [here](https://sourceforge.net/mailarchive/forum.php?forum_name=indimail-support)
2. indimail-devel - You can subscribe [here](https://lists.sourceforge.net/lists/listinfo/indimail-devel). You can mail [indimail-devel](mailto:indimail-devel@lists.sourceforge.net) for development activities. Old discussions can be seen [here](https://sourceforge.net/mailarchive/forum.php?forum_name=indimail-devel)
3. indimail-announce - This is only meant for announcement of New Releases or patches. You can subscribe [here](http://groups.google.com/group/indimail)
4. Archive at [Google Groups](http://groups.google.com/group/indimail). This groups acts as a remote archive for indimail-support and indimail-devel.

There is also a [Project Tracker](http://sourceforge.net/tracker/?group_id=230686) for IndiMail (Bugs, Feature Requests, Patches, Support Requests)
