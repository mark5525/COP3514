# Makefile for building the project10_registration program

CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Targets and dependencies

all: project10_registration

student.o: student.c student.h
	$(CC) $(CFLAGS) -c student.c -o student.o

project10_registration.o: project10_registration.c student.h
	$(CC) $(CFLAGS) -c project10_registration.c -o project10_registration.o

project10_registration: student.o project10_registration.o
	$(CC) $(CFLAGS) student.o project10_registration.o -o project10_registration

clean:
	rm -f *.o project10_registration
