/* Initialize the reviewed 1,000-node, 24-byte-record pool. */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct Node {
    u32 next, previous;
    u8 flags[4];
    u32 value, unit, state;
} Node;
typedef char sc_observed_node_size[(sizeof(Node) == 24) ? 1 : -1];
#pragma code_seg(".clear")
static void clear_node(Node *node) {
    node->flags[0] = 0;
    node->unit = 0;
    node->state = 0;
    node->flags[1] = 0;
    node->value = 0;
    node->flags[3] = 0;
    node->flags[2] = 0;
}
#pragma code_seg(".pool")
void __fastcall sub_00403DB0(Node *nodes) {
    u32 *previous;
    u32 n;
    nodes[0].next = (u32)(nodes + 1);
    nodes[0].previous = 0;
    clear_node(nodes);
    for (previous = &nodes[1].previous, n = 998; n; --n, previous += 6) {
        *previous = (u32)((u8 *)previous - 28);
        previous[-1] = (u32)((u8 *)previous + 20);
        ((u8 *)previous)[4] = 0;
        previous[3] = 0;
        previous[4] = 0;
        ((u8 *)previous)[5] = 0;
        previous[2] = 0;
        ((u8 *)previous)[7] = 0;
        ((u8 *)previous)[6] = 0;
    }
    nodes[999].next = 0;
    nodes[999].previous = (u32)(nodes + 998);
    clear_node(nodes + 999);
    nodes[1000].next = (u32)nodes;
}
