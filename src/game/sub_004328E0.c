/* Encode the reviewed 44-byte record and its five typed references. */
typedef unsigned int u32;
typedef unsigned char u8;
typedef signed short s16;
typedef struct Unit {u8 bytes[336];} Unit;
typedef struct State {u8 bytes[460];} State;
typedef struct Node {u32 next,prev;u8 flags[8];u32 unit,state,objects[5];} Node;
typedef struct Object32 {u8 bytes[32];} Object32;
extern Object32 g_0067D400[];
extern Unit g_0059CCA8[];
extern State g_006AA090[];
extern u32 g_0069A604[];
extern s16 *g_006D5BFC;
#pragma code_seg(".unit")
static u32 encode_unit(u32 pointer) {
    u32 index;
    if (!pointer) return 0;
    index = (pointer - (u32)g_0059CCA8) / 336u + 1;
    if (index > 1700) return 0;
    return ((u32)*(u8 *)(pointer + 165) << 11) | index;
}
#pragma code_seg(".state")
static u32 encode_state(u32 pointer) {
    if (!pointer) return 0;
    return (pointer - (u32)g_006AA090) / 460u + 1;
}
#pragma code_seg(".link32")
static u32 encode32(u32 pointer) {
    if (pointer) pointer = (pointer - (u32)g_0067D400) / 32u + 1;
    return pointer;
}
#pragma code_seg(".object")
static u32 encode_object(u32 pointer) {
    u32 index, owner;
    if (!pointer) return 0;
    owner = *(u8 *)(pointer + 4);
    index = (pointer - g_0069A604[owner]) / 52u;
    if (index >= (u32)(int)*g_006D5BFC) return 0;
    return owner * 2500u + index + 1;
}
#pragma code_seg(".pool")
typedef char sc_observed_node_size[(sizeof(Node) == 44) ? 1 : -1];
void __stdcall sub_004328E0(Node *node) {
    u32 i;
    u32 *object;
    node->unit = encode_unit(node->unit);
    node->state = encode_state(node->state);
    for (i = 0, object = node->objects; i < 5; ++i, ++object) {
        switch (node->flags[i + 1]) {
        case 1: *object = encode_object(*object); break;
        case 2: *object = encode32(*object); break;
        case 3: *object = encode_state(*object); break;
        }
    }
}
