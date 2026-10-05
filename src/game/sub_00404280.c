/* Complete typed-pool initializer; zero preparation still differs in code order. */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct Five { u32 values[5]; } Five;
typedef struct Node {
    u32 next, previous;
    u8 flag, types[5], padding[2];
    u32 unit, state;
    Five references;
} Node;
typedef char sc_observed_node_size[(sizeof(Node) == 44) ? 1 : -1];
void *__cdecl memset(void *, int, u32);
void __cdecl _WriteBarrier(void);
#pragma intrinsic(memset, _WriteBarrier)
#pragma code_seg(".small")
static void clear_types(u8 *types) { memset(types, 0, 5); }
#pragma code_seg(".tail")
static void clear_references(Five *references) { memset(references, 0, 20); }
#pragma code_seg(".clear")
static void clear_node(Node *node) {
    node->flag = 0;
    node->unit = 0;
    node->state = 0;
    clear_types(node->types);
    clear_references(&node->references);
}
#pragma code_seg(".pool")
void __fastcall sub_00404280(Node *nodes) {
    u32 *previous;
    u32 remaining;
    nodes[0].previous = 0;
    nodes[0].next = (u32)(nodes + 1);
    clear_node(nodes);
    for (previous = &nodes[1].previous, remaining = 998; remaining;
         --remaining, previous += 11) {
        *previous = (u32)((u8 *)previous - 48);
        /* This width-preserving C choice retains the observed memory order. */
        ((volatile u32 *)previous)[-1] = (u32)((u8 *)previous + 40);
        _WriteBarrier();
        ((u8 *)previous)[4] = 0;
        previous[3] = 0;
        previous[4] = 0;
        clear_types((u8 *)previous + 5);
        clear_references((Five *)(previous + 5));
    }
    nodes[999].next = 0;
    nodes[999].previous = (u32)(nodes + 998);
    clear_node(nodes + 999);
    nodes[1000].next = (u32)nodes;
}
