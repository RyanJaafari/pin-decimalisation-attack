CC = gcc
CFLAGS = -Wall -Wextra -O2

OBJS = main.o pin.o verify.o attack.o

all: pinattack

pinattack: $(OBJS)
	$(CC) $(CFLAGS) -o pinattack $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) pinattack
