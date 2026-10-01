#ifndef STARCRAFT_REVERSE_UNIT_VIEW_H
#define STARCRAFT_REVERSE_UNIT_VIEW_H
// Minimal observed byte layout; deliberately avoids speculative full CUnit.
typedef unsigned char sc_u8;
typedef unsigned int sc_u32;
typedef struct UnitView {
    sc_u8 unknown_000[0xdc];
    sc_u32 status;
    sc_u8 unknown_0e0[0x117 - 0xe0];
    sc_u8 lockdown_timer;
    sc_u8 unknown_118;
    sc_u8 stasis_timer;
    sc_u8 unknown_11a[0x124 - 0x11a];
    sc_u8 maelstrom_timer;
} UnitView;
_Static_assert(sizeof(sc_u32) == 4, "32-bit field required");
_Static_assert(__builtin_offsetof(UnitView, status) == 0xdc, "status offset");
_Static_assert(__builtin_offsetof(UnitView, lockdown_timer) == 0x117, "lockdown offset");
_Static_assert(__builtin_offsetof(UnitView, stasis_timer) == 0x119, "stasis offset");
_Static_assert(__builtin_offsetof(UnitView, maelstrom_timer) == 0x124, "maelstrom offset");
#endif
