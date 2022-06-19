# Version
VERSION = 0.1

# Paths
PREFIX    = /usr/local
MANPREFIX = ${PREFIX}/share/man

# Includes and Libs
INCS =
LIBS =

# Flags
CPPFLAGS   = -DVERSION=\"${VERSION}\"
EXTRAFLAGS = -g
CFLAGS     = -ansi -pedantic -Wall -Wextra -Wno-deprecated-declarations ${EXTRAFLAGS} ${INCS} ${CPPFLAGS} ${RELEASEFLAGS}
LDFLAGS    = ${LIBS}

# Compiler and Linker
CC = cc
