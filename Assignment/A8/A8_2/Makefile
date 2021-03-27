CFLAGS += -std=gnu11 -g
EXES = trunc
OBJS = list.o trunc.o 

all: $(EXES)

trunc:   trunc.o list.o

clean:
	rm -f $(EXES) $(OBJS)
	rm -rf $(LIBS)
tidy:
	rm -f $(OBJS)
