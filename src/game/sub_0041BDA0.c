#if defined(_MSC_VER)
#define PRIVATE_LEAF __declspec(noinline)
#else
#define PRIVATE_LEAF __attribute__((noinline))
#endif
#pragma pack(push, 1)
typedef struct DialogLeaf {
    unsigned char padding[4]; short left, top, right, bottom;
    unsigned char gap[0x26]; struct DialogLeaf *parent;
} DialogLeaf;
#pragma pack(pop)
typedef char dialog_leaf_size_check[sizeof(DialogLeaf) == 0x36 ? 1 : -1];
typedef struct { int left, top, right, bottom; } RectLeaf;
static PRIVATE_LEAF unsigned int sub_0041BDA0(const DialogLeaf *dialog, const RectLeaf *rect) {
    int left = dialog->parent->left;
    int top = dialog->parent->top;
    if (dialog->left + left <= rect->right &&
        dialog->top + top <= rect->bottom &&
        dialog->right + left >= rect->left &&
        dialog->bottom + top >= rect->top) {
        return 1;
    }
    return 0;
}
/* Independently authored compiler-context caller, not a reconstructed game routine. */
unsigned int compiler_context_0041BDA0(const DialogLeaf *dialog, const RectLeaf *rect) {
    return sub_0041BDA0(dialog, rect);
}
