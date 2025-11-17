#include <stdint.h>

#include "libopensc/opensc.h"

void *popeye_make_object(uint64_t size);

void *popeye_make_message();

uint32_t popeye_make_message_length();

int popeye_main()
{
    uint8_t *message = popeye_make_message();
    uint64_t size = popeye_make_message_length();
    sc_context_t *ctx = popeye_make_object(sizeof(sc_context_t));
    sc_apdu_t *apdu = popeye_make_object(sizeof(sc_apdu_t));
    sc_bytes2apdu(ctx, message, size, apdu);
    return 0;
}
