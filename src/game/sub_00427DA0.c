typedef unsigned char u8;
typedef unsigned long u32;
#if defined(_MSC_VER)
#define FASTCALL __fastcall
#define NOINLINE __declspec(noinline)
#else
#define FASTCALL __attribute__((fastcall))
#define NOINLINE __attribute__((noinline))
#endif
typedef u32 (FASTCALL *action_proc)(u8 *);
static NOINLINE u32 sub_00427DA0(u8 *trigger)
{
    u32 result;
    u8 index, kind;
    u8 *action;
    if (trigger[0xF] != 13) return 1;
    *(u32 *)(trigger + 0x940) |= 1;
    result = 1;
    do {
        index = trigger[0x95F];
        if (index >= 64) break;
        action = trigger + (index + 10) * 32;
        if (action[0x1C] & 2) {
            trigger[0x95F] = index + 1;
        } else {
            kind = action[0x1A];
            if (!kind) { trigger[0x95F] = 64; break; }
            result = ((action_proc *)0x00519E50)[kind](action);
            if (!result) break;
            ++trigger[0x95F];
        }
    } while (result);
    if (trigger[0x95F] < 64) return 0;
    trigger[0x95F] = 0;
    *(u32 *)(trigger + 0x940) &= ~1UL;
    return 1;
}
/* Hypothetical compiler context; not reconstructed or counted. */
u32 context(u8 *p) { return sub_00427DA0(p); }
