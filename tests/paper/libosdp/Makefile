CFLAGS += -I . -I src -I include -I utils/include
SRCS := $(wildcard src/*.c utils/src/*.c)
OBJS := $(SRCS:.c=.o)

main.a: main.o $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
