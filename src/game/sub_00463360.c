#if defined(_MSC_VER) && !defined(__clang__)
#define PRIVATE_LEAF __declspec(noinline)
#else
#define PRIVATE_LEAF __attribute__((noinline))
#endif
typedef struct UnitLeaf UnitLeaf;
typedef struct { unsigned char padding[0x80]; UnitLeaf *target; } LinkLeaf;
struct UnitLeaf {
    unsigned char padding[0x4c]; unsigned char owner;
    unsigned char gap[0x17]; unsigned short type;
    unsigned char gap2[6]; UnitLeaf *next;
    unsigned char gap3[0x60]; LinkLeaf *link; unsigned int ready;
};
typedef char unit_leaf_size_check[sizeof(UnitLeaf) == 0xD8 ? 1 : -1];
static PRIVATE_LEAF UnitLeaf *sub_00463360(const UnitLeaf *unit, unsigned int check_target, const UnitLeaf *excluded) {
    UnitLeaf *candidate = ((UnitLeaf *const *)0x006283F8u)[unit->owner];
    while (candidate) {
        if (candidate->type == 108 && candidate->ready) {
            UnitLeaf *target;
            if (!check_target) return candidate;
            target = candidate->link->target;
            if (!target || target == excluded || target->type == 108) return candidate;
        }
        candidate = candidate->next;
    }
    return (UnitLeaf *)0;
}
/* Compiler context only; not an independently reconstructed game routine. */
UnitLeaf *compiler_context_00463360(const UnitLeaf *unit, unsigned int check_target, const UnitLeaf *excluded) {
    return sub_00463360(unit, check_target, excluded);
}
