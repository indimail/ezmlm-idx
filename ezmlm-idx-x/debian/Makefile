indimaildir=$(shell head -1 ../conf-qmail)
prefix=$(shell head -1 ../conf-prefix)
cgibindir=$(shell head -1 ../conf-cgidir)
version=$(shell cat ../conf-version)
release=$(shell cat ../conf-release)
email=$(shell cat ../conf-email)
sysconfdir=$(shell head -1 ../conf-sysconfdir)
#

all: rules debian.tar.gz dummy.tar.gz ezmlm-idx.dsc \
	ezmlm-idx-Debian_11.dsc ezmlm-idx-Debian_10.dsc \
	ezmlm-idx-Debian_9.0.dsc ezmlm-idx-Debian_12.dsc \
	ezmlm-idx-Debian_13.dsc ezmlm-idx.postinst \
	ezmlm-idx.postrm _service

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
ezmlm-idx-Debian_13.dsc: ezmlm-idx-Debian_13.dsc.in ../conf-release ../conf-version
	$(edit) $@.in > $@
ezmlm-idx-Debian_12.dsc: ezmlm-idx-Debian_12.dsc.in ../conf-release ../conf-version
	$(edit) $@.in > $@
ezmlm-idx-Debian_11.dsc: ezmlm-idx-Debian_11.dsc.in ../conf-release ../conf-version
	$(edit) $@.in > $@
ezmlm-idx-Debian_10.dsc: ezmlm-idx-Debian_10.dsc.in ../conf-release ../conf-version
	$(edit) $@.in > $@
ezmlm-idx-Debian_9.0.dsc: ezmlm-idx-Debian_9.0.dsc.in ../conf-release ../conf-version
	$(edit) $@.in > $@
ezmlm-idx.postinst: ezmlm-idx.postinst.in ../conf-sysconfdir
	$(edit) $@.in > $@
ezmlm-idx.postrm: ezmlm-idx.postrm.in ../conf-sysconfdir
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

debian.tar.gz: copyright rules control changelog compat \
ezmlm-idx.postinst ezmlm-idx.postrm source/format Makefile
	cd .. && tar cf - debian/copyright debian/rules debian/control \
	debian/changelog debian/compat debian/ezmlm-idx.postinst debian/source \
	debian/ezmlm-idx.postrm | gzip > debian/$@
