
SRCS	= src/flop.c src/myterm.c

OBJS	= ${SRCS:.c=.o}

NAME	= flop

BINDIR  = bin

OSNAME	= ${BINDIR}/${NAME}_${HOSTTYPE}

PREFIX	= /usr/local/sbin

CLNF	!= libnet-config --cflags
DLNF	!= libnet-config --defines
LLNF	!= libnet-config --libs

CFLAGS	= -g -O -Wall ${CLNF} ${DLNF} -I./include

LDFLAGS	= -L/usr/pkg/lib -lpcap ${LLNF} -lncurses -ltermcap

CC	= cc
RM	= rm -f
LN	= ln -s
MKDIR	= mkdir -p

INSTALL	= install

${NAME}: ${OBJS}
	${MKDIR} ${BINDIR}
	${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} -o ${OSNAME}
	${RM} ${NAME}
	${LN} ${OSNAME} ${NAME}

${OSNAME}: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

install: ${OSNAME}
	${INSTALL} -d ${PREFIX}
	${INSTALL} -c -m 4710 ${NAME} ${PREFIX}

clean:
	${RM} ${OBJS} *~ */*~ *.core

fclean:	clean
	${RM} ${NAME} ${OSNAME}

re:	fclean ${OSNAME}


