/* Independent reconstruction; context helper only selects private registers. */
typedef unsigned int u32;
typedef unsigned short u16;
#if defined(_MSC_VER)
#define FAST __fastcall
#define NOINLINE __declspec(noinline)
#else
#define FAST __attribute__((fastcall))
#define NOINLINE __attribute__((noinline))
#endif
typedef struct Event { u32 code, zero, unknown; u16 kind, x, y, trailing; } Event;
typedef char Event_size_must_be_20[(sizeof(Event) == 20) ? 1 : -1];
typedef void (FAST *Callback)(void *, Event *);
static NOINLINE void sub_004196A0(u32 index, void *next)
{
    void **slots = (void **)0x006d5e40UL;
    void *old = slots[index];
    if (old) {
        Event event;
        u16 y = *(u16 *)0x006cddc8UL;
        u16 x = *(u16 *)0x006cddc4UL;
        event.y = y;
        event.kind = 14;
        event.code = 6;
        event.zero = 0;
        event.x = x;
        (*(Callback *)((unsigned char *)old + 0x2a))(old, &event);
    }
    slots[index] = next;
}
u32 context(u32 index, void *next)
{
    sub_004196A0(index, next);
    return ((u32 *)next)[6] + index;
}
