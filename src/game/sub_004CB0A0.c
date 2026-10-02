typedef unsigned int u32;
typedef struct Node { u32 unknown[3]; struct Node *next; struct Node *previous; } Node;
#ifdef _MSC_VER
#define NI __declspec(noinline)
#else
#define NI __attribute__((noinline))
#endif
extern void __stdcall sub_00410070(void *, const char *, u32, u32);
extern const char sc_source[];
#pragma code_seg(".scmatch")
static NI Node *sub_004CB0A0(Node *node, Node *head)
{
    if (node->previous) node->previous->next = node->next;
    if (node->next) node->next->previous = node->previous;
    if (node == head) {
        head = head->next;
        if (head) head->previous = 0;
    }
    sub_00410070(node, sc_source, 0x333u, 0u);
    return head;
}
#pragma code_seg(".scctx")
Node *hypothetical_context(Node *node, Node *head) { return sub_004CB0A0(node, head); }
