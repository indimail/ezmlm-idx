indimaildir=/var/indimail
prefix=/usr
cgibindir=/var/www/cgi-bin
version=$(shell cat ../conf-version)
release=$(shell cat ../conf-release)
email=$(shell cat ../conf-email)
sysconfdir=/etc/indimail
#

all: rules debian.tar.gz dummy.tar.gz ezmlm-idx.dsc \
	ezmlm-idx-Debian_11.dsc ezmlm-idx-Debian_10.dsc \
	ezmlm-idx-Debian_9.0.dsc _service

clean:
	/bin/rm -f *.dsc debian.tar.gz dummy.tar.gz _service

edit = sed \
	-e 's,@indimaildir\@,$(indimaildir),g' \
	-e 's,@sysconfdir\@,$(sysconfdir),g' \
	-e 's,@cgibindir\@,$(cgibindir),g' \
	-e 's,@version\@,$(version),g' \
	-e 's,@release\@,$(release),g' \
	-e 's,@email\@,$(email),g' \
	-e 's,@prefix\@,$(prefix),g'

ezmlm-idx.dsc: ezmlm-idx.dsc.in ../conf-release ../conf-version
	$(edit) $@.in > $@
ezmlm-idx-Debian_11.dsc: ezmlm-idx-Debian_11.dsc.in ../conf-release ../conf-version
	$(edit) $@.in > $@
ezmlm-idx-Debian_10.dsc: ezmlm-idx-Debian_10.dsc.in ../conf-release ../conf-version
	$(edit) $@.in > $@
ezmlm-idx-Debian_9.0.dsc: ezmlm-idx-Debian_9.0.dsc.in ../conf-release ../conf-version
	$(edit) $@.in > $@
_service: _service.in
	$(edit) $@.in > $@
changelog: ../doc/ChangeLog ../conf-version ../conf-release ../conf-email
	../catChangeLog --debian --name=ezmlm-idx --state=stable \
		--urgency=low ../doc/ChangeLog > $@
copyright: copyright.in ../conf-email
	$(edit) $@.in > $@
control: control.in ../conf-release ../conf-version ../conf-email
	$(edit) $@.in > $@
dummy.tar.gz: README
	tar cf - README |gzip > $@
debian.tar.gz: copyright rules control changelog compat
	tar cf - copyright rules control changelog compat | gzip > $@
