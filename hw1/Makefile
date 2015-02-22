SRCS=main.c shell.c process.c io.c parse.c 
EXECUTABLES=shell 

CC=gcc
CFLAGS=-g -Wall 
LDFLAGS=

OBJS=$(SRCS:.c=.o)

all: $(EXECUTABLES)

$(EXECUTABLES): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@  

.c.o:
	echo "$<"
	echo "$@"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(EXECUTABLES) $(OBJS)

echo:
	echo "$(OBJS)"
