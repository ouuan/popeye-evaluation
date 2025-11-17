CFLAGS += -I src
SRCS := src/libopensc/apdu.c
OBJS := $(SRCS:.c=.o)

main.a: main.o $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
