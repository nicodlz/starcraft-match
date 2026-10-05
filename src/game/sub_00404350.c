/* Serialize the reviewed 1,000-record pool with its actual C encoder. */
#include "sub_004328E0.c"
void *__cdecl memset(void *, int, u32);
#pragma intrinsic(memset)
#pragma code_seg(".clear")
static void clear_node(Node *node) {
    node->flags[0] = 0;
    node->unit = 0;
    node->state = 0;
    memset(node->flags + 1, 0, 5);
    memset(node->objects, 0, 20);
}
#pragma code_seg(".ulink")
static u32 encode_link(u32 pointer, Node *nodes) {
    if (!pointer) return 0;
    return (pointer - (u32)nodes) / 44u + 1;
}
#pragma code_seg(".pack")
__declspec(noinline) static void __fastcall sub_00404350(Node *nodes) {
    Node *node;
    u32 n;
    for (node = (Node *)nodes[1000].next; node; node = (Node *)node->next)
        clear_node(node);
    for (node = nodes, n = 1000; n; --n, ++node) {
        sub_004328E0(node);
        node->next = encode_link(node->next, nodes);
        node->prev = encode_link(node->prev, nodes);
    }
    nodes[1000].next = encode_link(nodes[1000].next, nodes);
}
#pragma code_seg(".anchor")
void __stdcall compiler_anchor_00404350(Node *nodes) {
    sub_00404350(nodes);
}
