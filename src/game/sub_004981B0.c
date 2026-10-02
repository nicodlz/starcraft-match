typedef char sc_unsigned_is_32[(sizeof(unsigned int) == 4) ? 1 : -1];
typedef char sc_pointer_is_32[(sizeof(void *) == 4) ? 1 : -1];
struct NodeView {
    unsigned int previous;
    struct NodeView *link_04;
    unsigned short value_08;
    unsigned short pad;
    unsigned short value_0c;
};
struct ListView { unsigned char pad[0x1c]; struct NodeView *head_1c; };
#if defined(_MSC_VER) && !defined(__clang__)
#define SC_OFFSET(type, field) ((unsigned int)&((type *)0)->field)
#else
#define SC_OFFSET(type, field) __builtin_offsetof(type, field)
#endif
typedef char sc_link_at_04[(SC_OFFSET(struct NodeView, link_04) == 4) ? 1 : -1];
typedef char sc_value_at_08[(SC_OFFSET(struct NodeView, value_08) == 8) ? 1 : -1];
typedef char sc_flags_at_0c[(SC_OFFSET(struct NodeView, value_0c) == 12) ? 1 : -1];
typedef char sc_head_at_1c[(SC_OFFSET(struct ListView, head_1c) == 28) ? 1 : -1];
#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
#define SC_FASTCALL __fastcall
#else
#define SC_NOINLINE __attribute__((noinline))
#define SC_FASTCALL __attribute__((fastcall))
#endif
/* Only the recorded MSVC static leaf uses the observed EAX input convention. */
static SC_NOINLINE void sub_004981B0(struct ListView *sprite) {
    struct NodeView *image = sprite->head_1c;
    while (image) {
        unsigned short type = image->value_08;
        if (type >= 0x188 && type <= 0x194) goto found;
        image = image->link_04;
    }
    image = sprite->head_1c;
    while (image) {
        unsigned short type = image->value_08;
        if (type >= 0x3be && type <= 0x3bf) goto found;
        image = image->link_04;
    }
    return;
found:
    {
        unsigned short flags = image->value_0c;
        if (flags & 0x40u) image->value_0c = (unsigned short)((flags & 0xffbfu) | 1u);
    }
}
/* Independent compiler context only; not a reconstructed game caller. */
void SC_FASTCALL independent_probe_004981B0(struct ListView *sprite) { sub_004981B0(sprite); }
