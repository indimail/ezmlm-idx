indimaildir=/var/indimail
prefix=/usr
cgibindir=/var/www/cgi-bin
version=$(shell sed -e 's/^.*-//' -e q ../VERSION )
release=$(shell cat ../conf-release)
sysconfdir=/etc/indimail
#

all: rules debian.tar.gz dummy.tar.gz ezmlm-idx.dsc \
	ezmlm-idx-Debian_10.dsc ezmlm-idx-Debian_9.0.dsc _service

clean:
	/bin/rm -f *.dsc debian.tar.gz dummy.tar.gz _service

edit = sed \
	-e 's,@indimaildir\@,$(indimaildir),g' \
	-e 's,@sysconfdir\@,$(sysconfdir),g' \
	-e 's,@cgibindir\@,$(cgibindir),g' \
	-e 's,@version\@,$(version),g' \
	-e 's,@release\@,$(release),g' \
	-e 's,@prefix\@,$(prefix),g'

ezmlm-idx.dsc: ezmlm-idx.dsc.in ../conf-release ../VERSION Makefile
	$(edit) $@.in > $@
ezmlm-idx-Debian_10.dsc: ezmlm-idx-Debian_10.dsc.in ../conf-release ../VERSION Makefile
	$(edit) $@.in > $@
ezmlm-idx-Debian_9.0.dsc: ezmlm-idx-Debian_9.0.dsc.in ../conf-release ../VERSION Makefile
	$(edit) $@.in > $@
_service: _service.in
	$(edit) $@.in > $@
control: control.in ../conf-release ../VERSION
	$(edit) $@.in > $@
changelog: changelog.in ../conf-release ../VERSION
	(cat $@.in; echo "";\
	echo " -- Manvendra Bhangui <manvendra@indimail.org>  `date +'%a, %d %b %Y %H:%M:%S %z'`" )| $(edit) > $@
dummy.tar.gz: README
	tar cf - README |gzip > $@
debian.tar.gz: copyright rules control changelog compat
	tar cf - copyright rules control changelog compat |gzip > $@
