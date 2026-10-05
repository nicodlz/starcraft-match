/* Restore the reviewed 44-byte record, retaining the compiler's switch table. */
typedef unsigned int u32;
__declspec(noinline) u32 __fastcall sub_00437290(u32 id);
#pragma code_seg(".callee")
#include "sub_00437290.c"
typedef struct Unit { u8 bytes[336]; } Unit;
typedef struct State { u8 bytes[460]; } State;
typedef struct Object32 { u8 bytes[32]; } Object32;
typedef struct Node {
    u32 next, previous;
    u8 flags[8];
    u32 unit, state, objects[5];
} Node;
extern Unit g_0059CCA8[];
extern State g_006AA090[];
extern Object32 g_0067D400[];
typedef char sc_observed_node_size[(sizeof(Node) == 44) ? 1 : -1];
#pragma code_seg(".unitdec")
static u32 decode_unit(u32 id) {
    return id ? (u32)&g_0059CCA8[(id & 2047u) - 1] : 0;
}
#pragma code_seg(".sdec")
static u32 decode_state(u32 id) {
    if (!id) return 0;
    return (u32)&g_006AA090[id - 1];
}
#pragma code_seg(".objdec")
static Object32 *decode32(u32 id) {
    if (!id) return 0;
    return &g_0067D400[id - 1];
}
#pragma code_seg(".decode")
__declspec(noinline) static void __fastcall sub_00432810(Node *node) {
    u32 i, *object;
    node->unit = decode_unit(node->unit);
    node->state = decode_state(node->state);
    for (i = 0, object = node->objects; i < 5; ++i, ++object) {
        switch (node->flags[i + 1]) {
        case 0: break;
        case 1: *object = sub_00437290(*object); break;
        case 2: *object = (u32)decode32(*object); break;
        case 3: *object = decode_state(*object); break;
        case 4: *object = 0; break;
        case 5: *object = 0; break;
        case 6: *object = 0; break;
        case 7: *object = 0; break;
        case 8: *object = 0; break;
        default: *object = 0; break;
        }
    }
}
#ifndef SC_NODE44_RESTORE_COMPONENT
#pragma code_seg(".anchor")
void __stdcall compiler_anchor_00432810(Node *node) {
    sub_00432810(node);
}
#endif
