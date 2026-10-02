#include "reverse/unit_leaf_views.h"
/* Observed ECX input and DWORD 0/1 return in EAX. No null or index checks. */
__attribute__((fastcall)) unsigned int sub_00473490(const UnitTypeLeafView *unit) {
    const unsigned int *base_properties = (const unsigned int *)0x00664080u;
    return (base_properties[unit->unit_type] >> 13) & 1u;
}
