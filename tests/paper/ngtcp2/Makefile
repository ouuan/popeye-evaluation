CFLAGS += -I lib -I lib/includes
SRCS := $(wildcard lib/*.c)
OBJS := $(SRCS:.c=.o)

main.a: lib/includes/ngtcp2/version.h main.o $(OBJS)
	$(AR) $(ARFLAGS) $@ main.o $(OBJS)

lib/includes/ngtcp2/version.h:
	echo '#define NGTCP2_VERSION "0.0.0"' > $@
	echo '#define NGTCP2_VERSION_NUM 0' >> $@
