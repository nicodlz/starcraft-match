/* Restore the reviewed list headers and six fixed-width unit references. */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct Unit { u8 bytes[336]; } Unit;
typedef struct State { u32 fields[115]; } State;
typedef struct Header { u32 base, head; } Header;
typedef struct Node24 { u8 bytes[24]; } Node24;
typedef struct Node44 { u8 bytes[44]; } Node44;
extern Unit g_0059CCA8[];
extern Node44 g_0069F468[];
typedef char sc_observed_state_size[(sizeof(State) == 460) ? 1 : -1];
#pragma code_seg(".l24")
static void decode_list24(Header *header) {
    u32 id = header->head;
    header->base = 0x006B5448u;
    if (id) id = (u32)((Node24 *)0x006B5448u + id - 1);
    header->head = id;
}
#pragma code_seg(".l44")
static void decode_list44(Header *header) {
    u32 id = header->head;
    header->base = (u32)g_0069F468;
    if (id) id = (u32)&g_0069F468[id - 1];
    header->head = id;
}
#pragma code_seg(".uunit")
static u32 decode_unit(u32 id) {
    return id ? (u32)&g_0059CCA8[(id & 0x7FFu) - 1] : 0;
}
#pragma code_seg(".restore")
__declspec(noinline) static void __fastcall sub_00403CB0(State *state) {
    decode_list24((Header *)&state->fields[2]);
    decode_list44((Header *)&state->fields[4]);
    state->fields[11] = decode_unit(state->fields[11]);
    state->fields[12] = decode_unit(state->fields[12]);
    state->fields[13] = decode_unit(state->fields[13]);
    state->fields[14] = decode_unit(state->fields[14]);
    state->fields[10] = decode_unit(state->fields[10]);
    state->fields[9] = decode_unit(state->fields[9]);
}
#ifndef SC_STATE_RESTORE_COMPONENT
#pragma code_seg(".anchor")
void __stdcall compiler_anchor_00403CB0(State *state) {
    sub_00403CB0(state);
}
#endif
