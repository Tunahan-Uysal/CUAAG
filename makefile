CC = gcc
CFLAGS = -lm -fsanitize=address -Wall
INCLUDES = -Iincludes
LFLAGS = 
LIBS =
SRCS = src/main.c includes/image.c includes/ascii.c
OBJS = $(SRCS:.c=.o)
MAIN = main

all: $(MAIN)
	@echo Compiled
$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
clean:
	$(RM) *.o *- $(MAIN)
