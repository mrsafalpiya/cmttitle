# See UNLICENSE file for copyright and license details.

include config.mk

# Variables

DEP_DIR = dep
OBJ_DIR = obj
OUT_DIR = bin

BIN = cmttitle
OUT = ${OUT_DIR}/${BIN}
SRC = ${BIN}.c
DEP = $(wildcard ${DEP_DIR}/*.c)
OBJ = $(patsubst %.c, ${OBJ_DIR}/%.o, ${SRC}) $(patsubst ${DEP_DIR}/%.c, ${OBJ_DIR}/%.o, ${DEP})

# Targets

all: ${OUT}

release: EXTRAFLAGS = -O2 -DNDEBUG
release: clean
release: ${OUT}

${OUT}: ${OUT_DIR} ${OBJ_DIR} ${OBJ}
	${CC} ${CFLAGS} ${OBJ} ${LDFLAGS} -o $@

${OUT_DIR}:
	mkdir $@

${OBJ_DIR}:
	mkdir $@

${OBJ_DIR}/%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

${OBJ_DIR}/%.o: ${DEP_DIR}/%.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -rf ${OBJ_DIR} ${OUT_DIR}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ${OUT} ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/${BIN}

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/${BIN}

.PHONY: all clean release install uninstall
