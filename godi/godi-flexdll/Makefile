.include "../../mk/bsd.prefs.mk"

VERSION=	0.31
PKGNAME=	godi-flexdll-${VERSION}
PKGREVISION=	3
DISTNAME=	flexdll
DISTFILES=	flexdll-${VERSION}.tar.gz flexdll-bin-${VERSION}.zip
EXTRACT_ONLY=	flexdll-${VERSION}.tar.gz
CATEGORIES=	godi
MASTER_SITES=	http://alain.frisch.fr/flexdll/
MAINTAINER=	wodi@ml.ignorelist.com
HOMEPAGE=	http://alain.frisch.fr/flexdll.html
COMMENT=	flexdll emulates Unix-style dynamic linking on Win32

BUILD_DEPENDS+=	godi-ocaml>=0:../../godi/godi-ocaml

USE_GMAKE=	yes

ALL_TARGET=	support flexlink.exe

# don't install via "make install"
INSTALL_DIRS=

# to get the right environment variables ....
MINGW_AUTOTOOLS_BUILD=yes

# now add by "../../mk/bsd.pkg.mk"
#PATH:=  ${BACKUPDIR}/bin:${PATH}

.if defined(W32PORT) 

.if ${W32PORT} == "mingw" 
DEINSTALL_SCRIPT_FILE=files/deinstall
INSTALL_SCRIPT_FILE=files/install
ADD_ENV= ${MAKE_ENV} GODI_PREFIX=${LOCALBASE}


.if defined(MINGW_WORDSIZE) && ${MINGW_WORDSIZE} == "64"
MAKE_FLAGS+=	CHAINS=mingw64
.else
MAKE_FLAGS+=	CHAINS=mingw
.endif

.endif

.elif defined(W32PORT) && ${W32PORT} == "cygwin" 
MAKE_FLAGS+=	CHAINS=cygwin
.endif

# On windows (both mingw and cygwin), check for GODI_BOOT_FLEXDLL
.if ${OPSYS} == "CYGWIN" && defined(GODI_BOOT_FLEXDLL)
PATH:=          ${GODI_BOOT_FLEXDLL}:${PATH}
MAKE_ENV+=      FLEXDIR=${GODI_BOOT_FLEXDLL}/../lib/flexdll
.endif

post-extract:
	cp files/config_reader* ${WRKSRC:Q}
	@cd ${WRKDIR:Q} && \
	  ${MKDIR} add && cd add && \
	  unzip -q ${DISTDIR}/flexdll-bin-${VERSION}.zip


pre-configure:
.if !defined(OPSYS) || ${OPSYS} != "CYGWIN"
	@echo "*********************************************"
	@echo "*** flexdll is only available for Windows ***"
	@echo "*********************************************"
	@false
.endif

post-install:
	${MKDIR} ${PREFIX}/bin ${PREFIX}/include ${PREFIX}/lib/flexdll
	${MKDIR} ${PREFIX}/doc/godi-flexdll
	${INSTALL} -m 0755 ${WRKSRC}/flexlink.exe ${PREFIX}/bin
	${INSTALL} -m 0644 ${WRKSRC}/flexdll.h ${PREFIX}/include
	for file in flexdll.h flexdll_*.o *.manifest ; do \
	   ${INSTALL} -m 0644 ${WRKSRC}/$$file ${PREFIX}/lib/flexdll; \
	done
.for  f in flexdll_cygwin.o flexdll_initer_cygwin.o \
	   flexdll_mingw.o flexdll_initer_mingw.o \
	   flexdll_mingw64.o flexdll_initer_mingw64.o \
	   flexdll_msvc.obj flexdll_initer_msvc.obj \
	   flexdll_msvc64.obj flexdll_initer_msvc64.obj
	@if [ ! -f ${PREFIX:Q}/lib/flexdll/${f:Q} ]; then \
	   ${INSTALL} -m 0644 ${WRKDIR:Q}/add/${f:Q} ${PREFIX:Q}/lib/flexdll ; \
	fi
.endfor
	@for file in LICENSE README CHANGES flexdll.c flexdll_initer.c default.manifest default_amd64.manifest; do \
	    ${INSTALL} -m 0644 ${WRKSRC}/$$file ${PREFIX}/doc/godi-flexdll/; \
	done
.if defined(W32PORT) && ${W32PORT} == "mingw"
	@${SETENV} ${ADD_ENV} bash files/install a POST-INSTALL
.endif

.include "../../mk/bsd.pkg.mk"
