#include "reverse/unit_view.h"
// Observed: EAX input, EAX 0/1 output. regparm(1) expresses that ABI on i386.
// Native host tests use their ordinary ABI; they only check candidate semantics.
#if defined(__i386__)
#define SC_EAX_ARG __attribute__((regparm(1)))
#else
#define SC_EAX_ARG
#endif
// Non-null pointer is a precondition: the original immediately dereferences it.
SC_EAX_ARG int sub_004020B0(const UnitView *unit) {
    if ((unit->status & 0x400u) != 0) return 1;
    if (unit->lockdown_timer != 0) return 1;
    if (unit->stasis_timer != 0) return 1;
    if (unit->maelstrom_timer != 0) return 1;
    return 0;
}
