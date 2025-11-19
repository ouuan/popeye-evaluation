#include <assert.h>
#include <stdint.h>

void *popeye_make_object(uint64_t size);

void *popeye_make_message();

uint32_t popeye_make_message_length();

struct interface
{
    uint64_t padding[35];
};

void parse_packet(const unsigned char *from, struct interface *ifp, const unsigned char *packet,
                  int packetlen);

int popeye_main()
{
    uint8_t *buf = popeye_make_message();
    uint32_t len = popeye_make_message_length();
    unsigned char *from = popeye_make_object(sizeof(char));
    struct interface *ifp = popeye_make_object(sizeof(struct interface));
    parse_packet(from, ifp, buf, len);
    return 0;
}
