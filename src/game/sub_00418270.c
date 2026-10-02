/* Independent C reconstruction; compilation context is hypothetical. */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define FASTCALL __fastcall
#else
#define NOINLINE __attribute__((noinline))
#define FASTCALL __attribute__((fastcall))
#endif
#define U32(p,n) (*(u32 *)((u8 *)(p)+(n)))
#define U16(p,n) (*(u16 *)((u8 *)(p)+(n)))
#define PTR(p,n) (*(void **)((u8 *)(p)+(n)))
struct Event { u32 type; u32 zero; u32 unspecified; u16 code; u16 x; u16 y; u16 unspecified2; };
typedef int (FASTCALL *Callback)(void *, struct Event *);
static NOINLINE int sub_00418270(void *node, u32 mask)
{
    void *child;
    u32 flags;
    u16 hotkey;
    struct Event event;
    if (U16(node,0x22)) node=PTR(node,0x32);
    child=PTR(node,0x42);
    while (child && !(U32(child,0x18)&mask)) child=PTR(child,0);
    if (!child) return 0;
    flags=U32(child,0x18);
    if (!(flags&8) || (flags&2)) return 0;
    hotkey=U16(child,0x20);
    if (hotkey==0xffff) return 0;
    if (!(hotkey&0x8000) && !(flags&0x10)) return 0;
    { u16 y=*(u16 *)0x006CDDC8;
    u16 x=*(u16 *)0x006CDDC4;
    event.y=y;
    event.code=0xE;
    event.type=3;
    event.zero=0;
    event.x=x;
    }
    return (*(Callback *)((u8 *)child+0x2A))(child,&event);
}
int hypothetical_context(void *node, u32 mask) { return sub_00418270(node,mask); }
