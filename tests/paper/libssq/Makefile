CFLAGS += -I include -I src
SRCS := $(wildcard src/*.c src/**/*.c)
OBJS := $(SRCS:.c=.o)

main.a: main.o $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
