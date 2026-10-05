/* Encode the reviewed list headers and six unit references in a 460-byte record. */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct State { u32 fields[115]; } State;
typedef struct Header { u32 base, head; } Header;
typedef char sc_state_size[(sizeof(State) == 460) ? 1 : -1];
extern u8 g_0059CCA8[];
#pragma code_seg(".uunit")
static u32 encode_unit(u32 unit) {
    u32 id;
    if (!unit) return 0;
    id = (unit - (u32)g_0059CCA8) / 336u + 1;
    if (id > 1700) return 0;
    return ((u32)*(u8 *)(unit + 165) << 11) | id;
}
#pragma code_seg(".hlist")
static void encode_list(Header *header, u32 stride) {
    u32 id = header->head;
    if (!id) id = 0;
    else id = (id - header->base) / stride + 1;
    header->head = id;
    header->base = 0;
}
#pragma code_seg(".root")
__declspec(noinline) static void __fastcall sub_00403AE0(State *state) {
    encode_list((Header *)&state->fields[2], 24u);
    encode_list((Header *)&state->fields[4], 44u);
    state->fields[11] = encode_unit(state->fields[11]);
    state->fields[12] = encode_unit(state->fields[12]);
    state->fields[13] = encode_unit(state->fields[13]);
    state->fields[14] = encode_unit(state->fields[14]);
    state->fields[10] = encode_unit(state->fields[10]);
    state->fields[9] = encode_unit(state->fields[9]);
}
#ifndef SC_STATE_COMPONENT
#pragma code_seg(".anchor")
void __stdcall compiler_anchor_00403AE0(State *state) {
    sub_00403AE0(state);
}
#endif
