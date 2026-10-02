#include "reverse/unit_leaf_views.h"
/* i386 regcall assigns the two inputs EAX and ECX; only CL is consumed. */
__attribute__((regcall)) void sub_00498150(SpriteTailLeafView *sprite,
                                         unsigned char new_vertical_offset) {
    ImageOffsetLeafView *image = sprite->image_tail;
    if (image->palette_type == 10 && image->vertical_offset != new_vertical_offset) {
        image->flags_low |= 1u;
        image->vertical_offset = new_vertical_offset;
    }
}
