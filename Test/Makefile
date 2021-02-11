CFLAGS += -std=gnu11 -g
EXES    = test

all:  $(EXES)
clean:
	rm -f $(EXES)

test: test.c

# do not treat `all` and `clean` as file targets
.PHONY: all clean