CFLAGS=-Wall -g
LIBS=-lm

clean:
	rm -f riemann_sums

all:
	rm -f riemann_sums
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) riemann_sums.c -o riemann_sums $(LIBS)
	./riemann_sums
