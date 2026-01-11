#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

void *popeye_make_object(uint64_t size);

void *popeye_make_message();

uint32_t popeye_make_message_length();

int parse_packet(int8_t *pkt)
{
    int ctrl;
    if (pkt[5] == 0)
        ctrl = pkt[4] + 1;
    else
        ctrl = pkt[4] - 1;
    if (pkt[6] > 0)
        assert(ctrl == 0);
    else
        exit(1);
    int code = ((int)pkt[0] << 8) | pkt[1];
    assert(code == 10);
    int state;
    if (pkt[3] == 0)
        state = pkt[2] + 1;
    else
        state = pkt[2] - 1;
    return state;
}

int popeye_main()
{
    int8_t *message = popeye_make_message();
    uint32_t size = popeye_make_message_length();

    parse_packet(message);

    return 0;
}
