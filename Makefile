# Makefile for the smash program
CC = g++
# CFLAGS = -g -Wall
CFLAGS =-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG 
CCLINK = $(CC)
OBJS = smash.o commands.o signals.o data.o
RM = rm -f
# Creating the  executable
smash: $(OBJS)
	$(CCLINK) -o smash $(OBJS)
# Creating the object files
data.o: data.cpp data.hpp
commands.o: commands.cpp commands.h data.hpp
smash.o: smash.cpp commands.h data.hpp
signals.o: signals.cpp signals.hpp
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

