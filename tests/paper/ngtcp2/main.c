#include <assert.h>
#include <stdint.h>

#include "ngtcp2_conn.h"

void *popeye_make_object(uint64_t size);

void *popeye_make_message();

uint32_t popeye_make_message_length();

int popeye_main()
{
    uint8_t *message = popeye_make_message();
    uint64_t size = popeye_make_message_length();

    ngtcp2_max_frame *mfr = popeye_make_object(sizeof(ngtcp2_max_frame));

    ngtcp2_ssize nread = ngtcp2_pkt_decode_frame(&mfr->fr, message, size);
    assert(nread > 0);

    return 0;
}
