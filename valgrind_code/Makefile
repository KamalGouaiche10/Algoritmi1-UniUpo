#CFLAGS+=-Wall -Wextra -ansi -pedantic -g
CFLAGS+=-Wall -Wextra -std=c11 -pedantic -g

objects = dangling_ptr \
		  memleak \
		  wild_ptr

all: $(objects)

clean:
	$(RM) $(objects)
	$(RM) vgcore.*
