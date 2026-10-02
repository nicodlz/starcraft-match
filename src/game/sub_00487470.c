#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#define FAST __fastcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#define FAST __attribute__((fastcall))
#endif
typedef unsigned short U16;
typedef unsigned int U32;
struct Node { struct Node *previous, *next; U32 unknown, value; };
typedef int (FAST *Predicate)(U32);
static NOINLINE void STDCALL sub_00487470(U16 count,struct Node **head,struct Node **tail,struct Node *array,Predicate predicate)
{
    U32 i = 0;
    struct Node *current;
    for (; i < count; ++i) {
        if (predicate(array[i].value)) break;
    }
    if (i == count) {
        *head = 0;
        *tail = 0;
        return;
    }
    *head = array+i;
    *tail = array+i;
    array[i].previous = 0;
    array[i].next = 0;
    current = *head;
    ++i;
    for (; i < count; ++i) {
        struct Node *node = array+i;
        if (predicate(node->value)) {
            node->previous = 0;
            node->next = 0;
            if (*tail == current) *tail = node;
            node->previous = current;
            node->next = current->next;
            if (current->next != 0) current->next->previous = node;
            current->next = node;
            current = node;
        }
    }
}
/* Hypothetical compilation context only; uncounted. */
void context_00487470(U16 count,struct Node **head,struct Node **tail,struct Node *array,Predicate predicate)
{
    sub_00487470(count,head,tail,array,predicate);
}
