/* Independent fixed-slot predicate; no game process is executed. */
#if defined(_MSC_VER)
#define SC_STD __stdcall
#else
#define SC_STD __attribute__((stdcall))
#endif
struct Sub00428360View { unsigned char pad[0xdc]; unsigned flags; };
typedef char DwordWidth00428360[(sizeof(unsigned) == 4) ? 1 : -1];

unsigned SC_STD sub_00428360(unsigned ignored)
{
    unsigned state;
    struct Sub00428360View *unit;
    struct Sub00428360View * volatile *slot;
    state=((*(struct Sub00428360View * volatile *)0x00597248u)->flags >> 4)&1u;
    slot=(struct Sub00428360View * volatile *)0x00597208u;
    do {
        unit=*slot;
        if(unit) {
            if(state) {
                if(!(*(volatile unsigned char *)&unit->flags & 0x10u)) return 0;
            } else {
                if(*(volatile unsigned char *)&unit->flags & 0x10u) return 0;
            }
        }
        ++slot;
    } while ((int)slot<0x00597238);
    return 1;
}
