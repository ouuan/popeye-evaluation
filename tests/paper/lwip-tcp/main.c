#include <assert.h>
#include <stdint.h>

#include "lwip/netif.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"

void *popeye_make_object(uint64_t size);

void *popeye_make_message();

uint32_t popeye_make_message_length();

void tcp_input(struct pbuf *p, struct netif *inp);

int popeye_main()
{
    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, 0, PBUF_ROM);
    p->payload = popeye_make_message();
    p->len = p->tot_len = popeye_make_message_length();
    struct netif *inp = popeye_make_object(sizeof(struct netif));
    const u32_t old_err = lwip_stats.mib2.tcpinerrs;
    tcp_input(p, inp);
    assert(lwip_stats.mib2.tcpinerrs == old_err);
    return 0;
}
