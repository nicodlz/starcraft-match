#if defined(_MSC_VER)
/* C90 matching view; byte offsets are corroborated by the compiled accesses. */
typedef struct UnitView {
    unsigned char unknown_000[0xDC];
    unsigned int status;
    unsigned char unknown_0e0[0x117 - 0xE0];
    unsigned char lockdown_timer;
    unsigned char unknown_118;
    unsigned char stasis_timer;
    unsigned char unknown_11a[0x124 - 0x11A];
    unsigned char maelstrom_timer;
} UnitView;
typedef char Sub004020B0WidthCheck[sizeof(unsigned int) == 4 ? 1 : -1];

/* Static context lets this compiler select the observed EAX input ABI. */
static __declspec(noinline) int sub_004020B0(const UnitView *unit)
{
    if ((unit->status & 0x400u) || unit->lockdown_timer
        || unit->stasis_timer || unit->maelstrom_timer)
        return 1;
    return 0;
}

/* Compilation context only: not an original function or an ABI shim. */
int sc_compile_context_004020B0(const UnitView *unit)
{
    return sub_004020B0(unit);
}
#else
#include "reverse/unit_view.h"
/* Keep the exported symbol and native calling convention for existing tests. */
#if defined(__i386__)
#define SC_EAX_ARG __attribute__((regparm(1)))
#else
#define SC_EAX_ARG
#endif
SC_EAX_ARG int sub_004020B0(const UnitView *unit)
{
    if ((unit->status & 0x400u) != 0) return 1;
    if (unit->lockdown_timer != 0) return 1;
    if (unit->stasis_timer != 0) return 1;
    if (unit->maelstrom_timer != 0) return 1;
    return 0;
}
#endif
