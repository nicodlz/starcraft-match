/* Static compiler context is uncounted; actual leaf input is EAX in MSVC. */
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define FASTCALL __fastcall
#else
#define NOINLINE __attribute__((noinline))
#define FASTCALL __attribute__((fastcall))
#endif
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Unit Unit;
struct Unit { u8 pad0[0x96]; u8 count; u8 pad97[0x45]; u32 status; u8 pade0[0x10]; Unit *prev; Unit *next; };
typedef char width_u32[(sizeof(u32) == 4) ? 1 : -1];
#if defined(_MSC_VER) && !defined(__clang__)
#define OFFSET(T,F) ((unsigned int)&((T *)0)->F)
#else
#define OFFSET(T,F) __builtin_offsetof(T,F)
#endif
typedef char offset_count[(OFFSET(Unit,count) == 0x96) ? 1 : -1];
typedef char offset_status[(OFFSET(Unit,status) == 0xdc) ? 1 : -1];
typedef char offset_prev[(OFFSET(Unit,prev) == 0xf0) ? 1 : -1];
typedef char offset_next[(OFFSET(Unit,next) == 0xf4) ? 1 : -1];
#define HEAD (*(Unit * volatile *)0x63ff5c)
static NOINLINE void sub_00491790(Unit *unit)
{
    Unit *head;
    u8 old = unit->count;
    unit->count = old + 1;
    if (old == 0 && !(unit->status & 0x100) && !unit->next) {
        unit->next = HEAD;
        unit->prev = 0;
        head = HEAD;
        if (head) head->prev = unit;
        HEAD = unit;
        *(volatile u32 *)0x68c1b0 = 1;
        *(volatile u8 *)0x68ac74 = 1;
        *(volatile u8 *)0x68c1f8 = 1;
        *(volatile u32 *)0x68c1e8 = 0;
        *(volatile u32 *)0x68c1ec = 0;
    }
}
void FASTCALL context_00491790(Unit *unit) { sub_00491790(unit); }
