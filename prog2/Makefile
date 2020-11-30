# For newbie to Makefile, make sure the build commands (line 4 and 7) 
# are a hard tab not spaces, or else make will not compile.

# all: hello.cpp
# 	$(CC) -o hello hello.cpp

# clean:
# 	rm -f hello

# Makefile for the smash program
CC = g++
# CFLAGS = -g -Wall
CFLAGS =-std=c++11 -Wall -g -Werror -pedantic-errors -DNDEBUG
CCLINK = $(CC)
OBJS = prog2.o
RM = rm -f
# Creating the  executable
prog: $(OBJS)
	$(CCLINK) -o prog2 $(OBJS)
# Creating the object files
prog2.o: prog2.cpp
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*
