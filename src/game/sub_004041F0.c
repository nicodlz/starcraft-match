/* Restore the reviewed 1,000-node pool with its original private EDX input. */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct Unit { u8 bytes[336]; } Unit;
typedef struct State { u8 bytes[460]; } State;
typedef struct Node {
    u32 next, previous;
    u8 flags[4];
    u32 value, unit, state;
} Node;
typedef char sc_observed_node_size[(sizeof(Node) == 24) ? 1 : -1];
extern Unit g_0059CCA8[];
extern State g_006AA090[];
#pragma code_seg(".uunit")
static u32 decode_unit(u32 id) {
    return id ? (u32)&g_0059CCA8[(id & 2047u) - 1] : 0;
}
#pragma code_seg(".state")
static u32 decode_state(u32 id) {
    if (id) id = (u32)&g_006AA090[id - 1];
    return id;
}
#pragma code_seg(".link")
static u32 decode_link(u32 id, Node *nodes) {
    if (!id) return 0;
    return (u32)(nodes + id - 1);
}
#pragma code_seg(".pool")
__declspec(noinline) static void __fastcall sub_004041F0(Node *nodes) {
    Node *node;
    u32 n;
    for (node = nodes, n = 1000; n; --n, ++node) {
        node->unit = decode_unit(node->unit);
        node->state = decode_state(node->state);
        node->next = decode_link(node->next, nodes);
        node->previous = decode_link(node->previous, nodes);
    }
    nodes[1000].next = decode_link(nodes[1000].next, nodes);
}
#pragma code_seg(".anchor")
void __stdcall compiler_anchor_004041F0(Node *nodes) {
    sub_004041F0(nodes);
}
