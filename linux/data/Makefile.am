cmugdir = $(prefix)/$(PACKAGE)/
cmug_DATA = pppoe

if HAVE_SYSTEMD
systemdsystemunit_DATA = cmcc@.service
cmcc@.service: $(srcdir)/cmcc@.service.in
	sed -e "s,[ ]cmugdir@,$(cmugdir),g" \
		< $< > $@
endif

EXTRA_DIST = pppoe \
						 cmcc@.service.in

CLEANFILES = pppoe \
						 cmcc@.service
