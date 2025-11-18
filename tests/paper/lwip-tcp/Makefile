CFLAGS += -I include -I . -I contrib/ports/unix/port/include
SRCS := $(wildcard core/*.c core/**/*.c)
OBJS := $(SRCS:.c=.o)

main.a: main.o $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
