.include "../../mk/bsd.prefs.mk"

VERSION=	111.17.00
ONAME=		bignum
PKG=		godi-${ONAME}
PKGNAME=        ${PKG}-${VERSION}
PKGREVISION=    0
DISTNAME=       bignum-111.17.00
DISTFILES=      bignum-111.17.00.tar.gz
CATEGORIES=     godi
MASTER_SITES=	https://ocaml.janestreet.com/ocaml-core/111.17.00/individual/
HOMEPAGE=       https://github.com/janestreet/bignum
COMMENT=        Core-flavoured wrapper around zarith's arbitrary-precision rationals

DEPENDS+=  godi-core_kernel>=111.17.00:../../godi/godi-core_kernel
DEPENDS+=  godi-ocaml>=4.00.1:../../godi/godi-ocaml
DEPENDS+=  godi-zarith>=1.2:../../godi/godi-zarith

BUILD_DEPENDS+=  godi-findlib>=1.3.2:../../godi/godi-findlib

WINOASIS=		yes

.include "../../mk/bsd.pkg.mk"
