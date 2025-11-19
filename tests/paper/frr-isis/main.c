#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "frr/isisd/isis_constants.h"

#define ETH_ALEN 6

void *popeye_make_object(uint64_t size);

void *popeye_make_message();

uint32_t popeye_make_message_length();

struct stream
{
    struct stream *next;
    size_t getp;         /* next get position */
    size_t endp;         /* last valid data position */
    size_t size;         /* size of data segment */
    unsigned char *data; /* data pointer */
};

enum isis_circuit_state
{
    C_STATE_NA,
    C_STATE_INIT, /* Connected to interface */
    C_STATE_CONF, /* Configured for ISIS    */
    C_STATE_UP,   /* CONN | CONF            */
};

struct nlpids
{
    uint8_t count;
    uint8_t nlpids[4]; /* FIXME: enough ? */
};

struct isis_circuit_arg
{
    int level;
    struct isis_circuit *circuit;
};

struct isis_bcast_info
{
    uint8_t snpa[ETH_ALEN];                           /* SNPA of this circuit */
    char run_dr_elect[ISIS_LEVELS];                   /* Should we run dr election ? */
    struct thread *t_run_dr[ISIS_LEVELS];             /* DR election thread */
    struct thread *t_send_lan_hello[ISIS_LEVELS];     /* send LAN IIHs in this
                                 thread */
    struct list *adjdb[ISIS_LEVELS];                  /* adjacency dbs */
    struct list *lan_neighs[ISIS_LEVELS];             /* list of lx neigh snpa */
    char is_dr[ISIS_LEVELS];                          /* Are we level x DR ? */
    uint8_t l1_desig_is[ISIS_SYS_ID_LEN + 1];         /* level-1 DR */
    uint8_t l2_desig_is[ISIS_SYS_ID_LEN + 1];         /* level-2 DR */
    struct thread *t_refresh_pseudo_lsp[ISIS_LEVELS]; /* refresh pseudo-node
                                 LSPs */
};

struct isis_p2p_info
{
    struct isis_adjacency *neighbor;
    struct thread *t_send_p2p_hello; /* send P2P IIHs in this thread  */
};

struct isis_passwd
{
    uint8_t len;
#define ISIS_PASSWD_TYPE_UNUSED 0
#define ISIS_PASSWD_TYPE_CLEARTXT 1
#define ISIS_PASSWD_TYPE_HMAC_MD5 54
#define ISIS_PASSWD_TYPE_PRIVATE 255
    uint8_t type;
/* Authenticate SNPs? */
#define SNP_AUTH_SEND 0x01
#define SNP_AUTH_RECV 0x02
    uint8_t snp_auth;
    uint8_t passwd[255];
};

struct isis_circuit
{
    enum isis_circuit_state state;
    uint8_t circuit_id; /* l1/l2 bcast CircuitID */
    time_t last_uptime;
    struct isis *isis;
    struct isis_area *area;      /* back pointer to the area */
    struct interface *interface; /* interface info from z */
    int fd;                      /* IS-IS l1/2 socket */
    int sap_length;              /* SAP length for DLPI */
    struct nlpids nlpids;
    /*
     * Threads
     */
    struct thread *t_read;
    struct thread *t_send_csnp[ISIS_LEVELS];
    struct thread *t_send_psnp[ISIS_LEVELS];
    struct isis_tx_queue *tx_queue;
    struct isis_circuit_arg level_arg[ISIS_LEVELS]; /* used as argument for threads */

    /* there is no real point in two streams, just for programming kicker */
    int (*rx)(struct isis_circuit *circuit, uint8_t *ssnpa);
    struct stream *rcv_stream; /* Stream for receiving */
    int (*tx)(struct isis_circuit *circuit, int level);
    struct stream *snd_stream; /* Stream for sending */
    int idx;                   /* idx in S[RM|SN] flags */
#define CIRCUIT_T_UNKNOWN 0
#define CIRCUIT_T_BROADCAST 1
#define CIRCUIT_T_P2P 2
#define CIRCUIT_T_LOOPBACK 3
    int circ_type;        /* type of the physical interface */
    int circ_type_config; /* config type of the physical interface */
    union
    {
        struct isis_bcast_info bc;
        struct isis_p2p_info p2p;
    } u;
    uint8_t priority[ISIS_LEVELS]; /* l1/2 IS configured priority */
    int pad_hellos;                /* add padding to Hello PDUs ? */
    char ext_domain;               /* externalDomain   (boolean) */
    int lsp_regenerate_pending[ISIS_LEVELS];
    uint64_t lsp_error_counter;

    /*
     * Configurables
     */
    char *tag;                              /* area tag */
    struct isis_passwd passwd;              /* Circuit rx/tx password */
    int is_type;                            /* circuit is type == level of circuit
                                             * differentiated from circuit type (media) */
    uint32_t hello_interval[ISIS_LEVELS];   /* hello-interval in seconds */
    uint16_t hello_multiplier[ISIS_LEVELS]; /* hello-multiplier */
    uint16_t csnp_interval[ISIS_LEVELS];    /* csnp-interval in seconds */
    uint16_t psnp_interval[ISIS_LEVELS];    /* psnp-interval in seconds */
    uint8_t metric[ISIS_LEVELS];
    uint32_t te_metric[ISIS_LEVELS];
    struct isis_ext_subtlvs *ext; /* Extended parameters (TE + Adj SID */
    int ip_router;                /* Route IP ? */
    int is_passive;               /* Is Passive ? */
    struct list *mt_settings;     /* IS-IS MT Settings */
    struct list *ip_addrs;        /* our IP addresses */
    int ipv6_router;              /* Route IPv6 ? */
    struct list *ipv6_link;       /* our link local IPv6 addresses */
    struct list *ipv6_non_link;   /* our non-link local IPv6 addresses */
    uint16_t upadjcount[ISIS_LEVELS];
#define ISIS_CIRCUIT_FLAPPED_AFTER_SPF 0x01
    uint8_t flags;
    bool disable_threeway_adj;
    struct
    {
        bool enabled;
        char *profile;
    } bfd_config;
    struct ldp_sync_info *ldp_sync_info;
    bool lfa_protection[ISIS_LEVELS];
    bool rlfa_protection[ISIS_LEVELS];
    uint32_t rlfa_max_metric[ISIS_LEVELS];
    struct hash *lfa_excluded_ifaces[ISIS_LEVELS];
    bool tilfa_protection[ISIS_LEVELS];
    bool tilfa_node_protection[ISIS_LEVELS];
    bool tilfa_link_fallback[ISIS_LEVELS];
    /*
     * Counters as in 10589--11.2.5.9
     */
    uint32_t adj_state_changes;          /* changesInAdjacencyState */
    uint32_t init_failures;              /* intialisationFailures */
    uint32_t ctrl_pdus_rxed;             /* controlPDUsReceived */
    uint32_t ctrl_pdus_txed;             /* controlPDUsSent */
    uint32_t desig_changes[ISIS_LEVELS]; /* lanLxDesignatedIntermediateSystemChanges
                                          */
    uint32_t rej_adjacencies;            /* rejectedAdjacencies */
    /*
     * Counters as in ietf-isis@2019-09-09.yang
     */
    uint32_t id_len_mismatches;        /* id-len-mismatch */
    uint32_t max_area_addr_mismatches; /* max-area-addresses-mismatch */
    uint32_t auth_type_failures;       /*authentication-type-fails */
    uint32_t auth_failures;            /* authentication-fails */

    uint32_t snmp_id; /* Circuit id in snmp */

    uint32_t snmp_adj_idx_gen;  /* Create unique id for adjacency on creation
                                 */
    struct list *snmp_adj_list; /* List in id order */

    // QOBJ_FIELDS;
};

int isis_handle_pdu(struct isis_circuit *circuit, uint8_t *ssnpa);

int popeye_main()
{
    uint8_t *buf = popeye_make_message();
    uint32_t len = popeye_make_message_length();
    struct isis_circuit *circuit = popeye_make_object(sizeof(struct isis_circuit));
    struct stream stream = {
        .next = NULL,
        .getp = 0,
        .endp = len,
        .size = len,
        .data = buf,
    };
    circuit->rcv_stream = &stream;
    uint8_t *ssnpa = popeye_make_object(sizeof(uint8_t));
    const int ret = isis_handle_pdu(circuit, ssnpa);
    assert(ret == ISIS_OK);
    return 0;
}
