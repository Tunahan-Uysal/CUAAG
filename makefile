CC = gcc
CFLAGS = -g -fsanitize=address -std=c99 -Wall
INCLUDES = -Iincludes
LFLAGS = 
LIBS = -lm
SRCS = src/main.c includes/image.c includes/ascii.c includes/creatematrix.c
OBJS = $(SRCS:.c=.o)
MAIN = main

all: $(MAIN)
	@echo Compiled
$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS) -o $(MAIN) $^
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
clean:
	$(RM) *.o *- $(MAIN)
