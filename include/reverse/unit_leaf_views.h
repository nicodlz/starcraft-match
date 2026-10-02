#ifndef STARCRAFT_UNIT_LEAF_VIEWS_H
#define STARCRAFT_UNIT_LEAF_VIEWS_H
/* Minimal layouts independently inferred from the pinned executable accesses. */
typedef struct UnitTypeLeafView {
    unsigned char unknown_000[0x64];
    unsigned short unit_type;
} UnitTypeLeafView;
_Static_assert(__builtin_offsetof(UnitTypeLeafView, unit_type) == 0x64, "unit type offset");
typedef struct ImageOffsetLeafView {
    unsigned char unknown_00[0x0a];
    unsigned char palette_type;
    unsigned char unknown_0b;
    unsigned char flags_low;
    unsigned char unknown_0d[2];
    unsigned char vertical_offset;
} ImageOffsetLeafView;
typedef struct SpriteTailLeafView {
    unsigned char unknown_00[0x20];
    ImageOffsetLeafView *image_tail;
} SpriteTailLeafView;
_Static_assert(__builtin_offsetof(SpriteTailLeafView, image_tail) == 0x20, "sprite tail offset");
_Static_assert(__builtin_offsetof(ImageOffsetLeafView, flags_low) == 0x0c, "image flags offset");
_Static_assert(__builtin_offsetof(ImageOffsetLeafView, vertical_offset) == 0x0f, "vertical offset");
#endif
