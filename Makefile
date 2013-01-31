# Name: Vikrum Nijjar Student ID: 1149287
# System: Linux cow 2.4.10 #1 SMP Sun Oct 7 12:09:41 PDT 2001 i686 unknown
# Compiler: gcc version 2.96 20000731 Red Hat Linux 7.1 2.96-81 glibc-2.2.4-19
# Assignment: 05 -- Source code parser:  introspective
#

CFLAGS=-Wall
CC=gcc
LIBS=lex.yy.c
DATASTRUCTS=list.o bitree.o bistree.o
OBJS=tokens.o debug.o traverse.o report.o clobber.o process.o\
	lookup.o aux.o handle_aux.o handle.o process_aux.o
DEPENDS=$(DATASTRUCTS) $(OBJS)
MODULE=introspective

all: $(MODULE)

$(MODULE): $(DEPENDS) introspective.c global.h extern.h
	$(CC) $(CFLAGS) -o $(MODULE) introspective.c $(DEPENDS) -lfl

tokens.o: $(LIBS)
	$(CC) $(CFLAGS)   -c -o $@ $< -DYY_NO_UNPUT

$(LIBS):
	flex tokens.lex

clean:
	rm -f $(MODULE) $(DEPENDS) $(LIBS) core

#./introspective global.h list_struct.h list.h list.c bitree.h bitree.c bistree.h \
# bistree.c debug.h debug.c traverse.h traverse.c report.h report.c process.h \
# process.c lookup.h lookup.c aux.h aux.c handle_aux.h handle_aux.c handle.h \
# handle.c clobber.h clobber.c process_aux.h process_aux.c introspective.c 
