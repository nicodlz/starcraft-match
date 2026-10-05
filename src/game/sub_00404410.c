/* Restore the reviewed 1,000-record pool with both actual C dependencies. */
#define SC_NODE44_RESTORE_COMPONENT 1
#include "sub_00432810.c"
#pragma code_seg(".ulink")
static u32 decode_link(u32 id, Node *nodes) {
    if (!id) return 0;
    return (u32)(nodes + id - 1);
}
#pragma code_seg(".unpack")
__declspec(noinline) static void __fastcall sub_00404410(Node *nodes) {
    Node *node;
    u32 n;
    for (node = nodes, n = 1000; n; --n, ++node) {
        sub_00432810(node);
        node->next = decode_link(node->next, nodes);
        node->previous = decode_link(node->previous, nodes);
    }
    nodes[1000].next = decode_link(nodes[1000].next, nodes);
}
#pragma code_seg(".anchor")
void __stdcall compiler_anchor_00404410(Node *nodes) {
    sub_00404410(nodes);
}
