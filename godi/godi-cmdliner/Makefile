.include "../../mk/bsd.prefs.mk"

VERSION= 	0.9.5
ONAME=		cmdliner
PKGNAME= 	godi-${ONAME}-${VERSION}  
PKGREVISION= 	0
DISTNAME=	cmdliner-${VERSION} 
DISTFILES=	${DISTNAME}.tbz  
CATEGORIES=	godi  
MASTER_SITES= 	http://erratique.ch/software/cmdliner/releases/ 
MAINTAINER=	andreas@ml.ignorelist.com
HOMEPAGE=	http://erratique.ch/software/cmdliner 
COMMENT=	library for declarative definition of command line interfaces

DEPENDS+=	godi-ocaml>=3.11:../../godi/godi-ocaml
BUILD_DEPENDS+= godi-findlib-[0-9]*:../../godi/godi-findlib
BUILD_DEPENDS+= godi-opam-installer>=1.0:../../godi/godi-opam-installer

PLIST_SRC=	${WRKDIR:Q}/.PLIST.${PKGBASE:Q}
IMAGE_DIR=	${WRKDIR:Q}/image


.if ${GODI_HAVE_OCAMLOPT} == "yes"
BUILD_SCRIPT=	${LOCALBASE:Q}/bin/ocaml.exe ${CYGWIN_ROOT:Q}${WRKSRC:Q}/pkg/build.ml native=true native-dynlink=true
.else
BUILD_SCRIPT=	${LOCALBASE:Q}/bin/ocaml.exe ${CYGWIN_ROOT:Q}${WRKSRC:Q}/pkg/build.ml
.endif

INSTALL_SCRIPT= bash ${PKGDIR:Q}/files/install.sh --prefix=${IMAGE_DIR:Q} --wrksrc=${WRKSRC:Q} \
		 --install-file=${ONAME:Q}.install --name=${PKGBASE:Q}

post-install:
	${MKDIR} ${IMAGE_DIR}/doc/${PKGBASE:Q}/html
	${CP} ${WRKSRC}/doc/* ${IMAGE_DIR}/doc/${PKGBASE:Q}/html
	cd ${IMAGE_DIR} && ${FIND} * ! -type d >${PLIST_SRC} && \
		${PAX} -rw -pp . ${LOCALBASE:Q}

.include "../../mk/bsd.pkg.mk"
