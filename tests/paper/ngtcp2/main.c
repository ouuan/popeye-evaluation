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

    ngtcp2_frame_decoder frd;
    ngtcp2_frame fr;

    ngtcp2_ssize nread = ngtcp2_frame_decoder_decode(&frd, &fr, message, size);
    assert(nread > 0);

    return 0;
}
