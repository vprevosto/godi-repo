# This file was automatically generated by godiva version 0.9.7
.include "../../mk/bsd.prefs.mk"

VERSION=        2.03.2
PKGNAME=        godi-calendar-${VERSION}
PKGREVISION=    1
DISTNAME=       calendar-2.03.2
DISTFILES=      calendar-2.03.2.tar.gz
CATEGORIES=     godi
MASTER_SITES=   http://forge.ocamlcore.org/frs/download.php/915/
MAINTAINER=     Julien Signoles <julien.signoles@gmail.com>
HOMEPAGE=       http://calendar.forge.ocamlcore.org/
COMMENT=        Operations over dates and times.

# confopt defaults:


AUTOGENERATE_PLIST = yes
PKG  =          godi-calendar
MAKE_FLAGS=     PREFIX=${PREFIX} BINDIR=${PREFIX}/bin MANDIR=${PREFIX}/man
DEPENDS+= godi-ocaml>=3.09:../../godi/godi-ocaml
BUILD_DEPENDS+= godi-findlib-[0-9]*:../../godi/godi-findlib

HAS_CONFIGURE = yes
CONFIGURE_ARGS+= --prefix ${PREFIX}
CONFIGURE_ENV+= ${BUILD_OCAMLFIND_ENV}

USE_GMAKE = yes

MAKE_ENV+=  ${BUILD_OCAMLFIND_ENV} PKGBASE=${PKGBASE:Q}

pre-configure-copy:
.	if exists(files)
	    cd files && ${PAX} -rw -pp . ${WRKSRC}
.	endif

pre-configure: pre-configure-copy

ALL_TARGET=     all
.if ${GODI_HAVE_OCAMLOPT} == "yes"
# ALL_TARGET+= opt
.endif

post-install:
	mkdir -p ${PREFIX}/doc/${PKG}
.	for DOC in CHANGES COPYING LGPL LICENSE README TODO
	    if [ -d ${WRKSRC}/${DOC} ]; then cd ${WRKSRC} && ${PAX} -rw -pp ${DOC} ${PREFIX}/doc/${PKG}; else install -m 0644 ${WRKSRC}/${DOC} ${PREFIX}/doc/${PKG}; fi
.	endfor

.include "../../mk/bsd.pkg.mk"
