CFLAGS += -Wall -Wextra -std=c11 -pedantic
CFLAGS += -g
CFLAGS += -I./include
LDFLAGS += -L./lib
LDLIBS += -lupoalglib -lm


.PHONY: all clean

all: test/bst_common_ancestor test/ht_linprob_avg_collisions

test/bst_common_ancestor: test/bst_common_ancestor.o exam.o
test/ht_linprob_avg_collisions: test/ht_linprob_avg_collisions.o exam.o

# Build exam.o from the actual source file
exam.o: exam20250124.c
	$(CC) $(CFLAGS) -c -o $@ exam20250124.c

clean:
	$(RM) test/bst_common_ancestor
	$(RM) test/ht_linprob_avg_collisions
	$(RM) *.o test/*.o
	$(RM) vgcore.* test/vgcore.*
