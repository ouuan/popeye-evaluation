#include <stdint.h>

#include "error.h"
#include "ssq/a2s/info.h"

void *popeye_make_object(uint64_t size);

void *popeye_make_message();

uint32_t popeye_make_message_length();

A2S_INFO *ssq_info_deserialize(const uint8_t payload[], size_t payload_len, SSQ_ERROR *error);

int popeye_main()
{
    uint8_t *message = popeye_make_message();
    uint64_t size = popeye_make_message_length();
    SSQ_ERROR *error = popeye_make_object(sizeof(SSQ_ERROR));
    ssq_info_deserialize(message, size, error);
    return 0;
}
