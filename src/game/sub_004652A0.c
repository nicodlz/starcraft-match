#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
typedef struct Object Object;
typedef struct Owner {
    unsigned char pad[192];
    Object *first0;
    Object *first1;
    unsigned char count0;
    unsigned char count1;
} Owner;
struct Object {
    unsigned char pad[192];
    Owner *owner;
    Object *link_c4;
    Object *link_c8;
    unsigned char tag;
};
typedef char ObjectSizeCheck[sizeof(Object) == 208 ? 1 : -1];
typedef char OwnerSizeCheck[sizeof(Owner) == 204 ? 1 : -1];
static NOINLINE void sub_004652A0(Object *p)
{
    Owner *owner = p->owner;
    if (!owner) {
        p->link_c4 = 0;
        p->link_c8 = 0;
        return;
    }
    if (p->link_c8)
        p->link_c8->link_c4 = p->link_c4;
    else if (p->tag)
        owner->first1 = p->link_c4;
    else
        owner->first0 = p->link_c4;
    if (p->tag)
        --p->owner->count1;
    else
        --p->owner->count0;
    if (p->link_c4)
        p->link_c4->link_c8 = p->link_c8;
}
/* Hypothetical static optimization context only, not a matched game function. */
void context_004652A0(Object *p) { sub_004652A0(p); }
