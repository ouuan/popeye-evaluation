#include <assert.h>
#include <stdint.h>

void parse(uint8_t *message, uint64_t size)
{
    assert(message[0] == message[1]);
    assert(message[1] == message[2]);
}
