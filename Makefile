#
# Makefile for the UM Program
# 
CC = gcc

IFLAGS  = -I/comp/40/build/include -I/usr/sup/cii40/include/cii
CFLAGS  = -g -std=gnu99 -Wall -Wextra -Werror -pedantic $(IFLAGS)
LDFLAGS = -g -L/comp/40/build/lib -L/usr/sup/cii40/lib64
LDLIBS  =  -lbitpack -l40locality -lcii40 -lm

INCLUDES = $(shell echo *.h) memory.h instructions.h loadProgram.h

############### Rules ###############

EXECS   = um writetests

all: $(EXECS)

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

um: um.o instructions.o memory.o loadProgram.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

writetests: umlabwrite.o umlab.o 
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -f $(EXECS)  *.o