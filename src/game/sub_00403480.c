/* Reviewed 52-byte pool record: list header and four unit references. */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct State { u32 fields[13]; } State;
typedef struct Header { u32 base, head; } Header;
typedef char sc_state_size[(sizeof(State) == 52) ? 1 : -1];
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
__declspec(noinline) static void __fastcall sub_00403480(State *state) {
    encode_list((Header *)&state->fields[11], 20u);
    state->fields[7] = encode_unit(state->fields[7]);
    state->fields[8] = encode_unit(state->fields[8]);
    state->fields[9] = encode_unit(state->fields[9]);
    state->fields[10] = encode_unit(state->fields[10]);
}
#pragma code_seg(".anchor")
void __stdcall compiler_anchor_00403480(State *state) {
    sub_00403480(state);
}
