#include <stdint.h>

void *popeye_make_object(uint64_t size);

void *popeye_make_message();

uint32_t popeye_make_message_length();

void parse(uint8_t *message, uint64_t size);

int popeye_main()
{
    uint8_t *message = popeye_make_message();
    uint64_t size = popeye_make_message_length();
    parse(message, size);
    return 0;
}
