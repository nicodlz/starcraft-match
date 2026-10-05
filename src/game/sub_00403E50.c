/* Serialize the reviewed 1,000-node pool and its unit/state references. */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct Node {
    u32 next, previous;
    u8 flags[4];
    u32 value, unit, state;
} Node;
typedef struct State { u8 bytes[460]; } State;
typedef char sc_observed_node_size[(sizeof(Node) == 24) ? 1 : -1];
extern State g_006AA090[];
extern u8 g_0059CCA8[];
void __cdecl _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
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
#pragma code_seg(".unit")
static u32 encode_unit(u32 unit) {
    u32 id;
    if (!unit) return 0;
    id = (unit - (u32)g_0059CCA8) / 336u + 1;
    if (id > 1700) return 0;
    return ((u32)*(u8 *)(unit + 165) << 11) | id;
}
#pragma code_seg(".state")
static u32 encode_state(u32 pointer) {
    if (!pointer) return 0;
    return (pointer - (u32)g_006AA090) / 460u + 1;
}
#pragma code_seg(".link")
static u32 encode_link(u32 pointer,Node *nodes) {
    if (!pointer) return 0;
    return (pointer - (u32)nodes) / 24u + 1;
}
/* The compiler-only barrier keeps the observed store before link reads.
 * Five explicit records retain the original loop layout without emitting a fence. */
#define ENCODE_RECORD(offset) do { \
    node = nodes + i + (offset); \
    node->unit = encode_unit(node->unit); \
    node->state = encode_state(node->state); \
    _ReadWriteBarrier(); \
    node->next = encode_link(node->next, nodes); \
    node->previous = encode_link(node->previous, nodes); \
} while (0)
#pragma code_seg(".pool")
void __stdcall sub_00403E50(Node *nodes) {
    Node *node = (Node *)nodes[1000].next;
    u32 i;
    while (node) {
        clear_node(node);
        node = (Node *)node->next;
    }
    for (i = 0; i < 1000; i += 5) {
        ENCODE_RECORD(0);
        ENCODE_RECORD(1);
        ENCODE_RECORD(2);
        ENCODE_RECORD(3);
        ENCODE_RECORD(4);
    }
    nodes[1000].next = encode_link(nodes[1000].next, nodes);
}
#undef ENCODE_RECORD
