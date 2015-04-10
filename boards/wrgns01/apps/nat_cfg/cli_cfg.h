
typedef struct clicmd_t {
    char       *name;
    int       (*action)();
    char       *help_msg;
} CLICMD_T;

#define IPIV(a,b,c,d) ((a<<24)+(b<<16)+(c<<8)+d)
#define IP3(a)        ((a>>24)&0xff)
#define IP2(a)        ((a>>16)&0xff)
#define IP1(a)        ((a>>8)&0xff)
#define IP0(a)        ((a)&0xff)

#define PROTOCOL_UDP 17
#define PROTOCOL_TCP 6
#define PROTOCOL_TCP_AND_UDP	0
