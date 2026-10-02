#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned char U8;
typedef unsigned int U32;
#pragma pack(push,1)
struct Packet { U8 tag, x, y; U32 value; };
#pragma pack(pop)
typedef char packet_size[sizeof(struct Packet)==7 ? 1 : -1];
typedef void (STDCALL *Callback)(const struct Packet *, U32, U32);
static NOINLINE void sub_00459DC0(const U8 *p)
{
    Callback callback = *(Callback *)0x0066fc00;
    if (callback != 0) {
        struct Packet packet;
        packet.x = p[8];
        packet.y = p[9];
        packet.value = *(const U32 *)(p+0x40);
        packet.tag = 5;
        callback(&packet, 7, p[0x3d]);
    }
}
/* Hypothetical compilation context only. */
void context_00459DC0(const U8 *p) { sub_00459DC0(p); }
