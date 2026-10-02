#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#define FAST __fastcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#define FAST __attribute__((fastcall))
#endif
typedef unsigned char U8;
struct Node { U8 unused[0xc0]; struct Node *first, *next; U8 count_first, count_next; };
typedef int (FAST *Callback)(struct Node *, void *);
static NOINLINE int STDCALL sub_00465200(struct Node *p, Callback callback, void *context)
{
    U8 count = p->count_first;
    struct Node *node = p->first;
    while (count != 0) {
        --count;
        if (callback(node, context) != 0) return 1;
        node = node->next;
    }
    count = p->count_next;
    node = p->next;
    while (count != 0) {
        --count;
        if (callback(node, context) != 0) return 1;
        node = node->next;
    }
    return 0;
}
/* Hypothetical compilation context only. */
int context_00465200(struct Node *p, Callback callback, void *context)
{
    return sub_00465200(p,callback,context);
}
