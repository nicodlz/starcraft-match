/* Initialize the reviewed 100-record, 460-byte-record pool. */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct Header { u32 base, head; } Header;
typedef struct State { u32 fields[115]; } State;
typedef char sc_observed_state_size[(sizeof(State) == 460) ? 1 : -1];
void *__cdecl memset(void *, int, u32);
#pragma intrinsic(memset)
#pragma code_seg(".header")
static void initialize_header(Header *header, u32 base) {
    header->base = base;
    header->head = 0;
}
#pragma code_seg(".clear")
static void initialize_fields(State *state) {
    memset(&state->fields[6], 0, 436);
    initialize_header((Header *)&state->fields[2], 0x6B5448u);
    initialize_header((Header *)&state->fields[4], 0x69F468u);
}
#pragma code_seg(".pool")
__declspec(noinline) static void __fastcall sub_00404550(State *states) {
    u32 *head;
    u32 n;
    states[0].fields[1] = 0;
    states[0].fields[0] = (u32)(states + 1);
    initialize_fields(states);
    for (head = &states[1].fields[5], n = 98; n; --n, head += 115) {
        head[-4] = (u32)((u8 *)head - 480);
        head[-5] = (u32)((u8 *)head + 440);
        memset(head + 1, 0, 436);
        initialize_header((Header *)(head - 3), 0x6B5448u);
        initialize_header((Header *)(head - 1), 0x69F468u);
    }
    states[99].fields[1] = (u32)(states + 98);
    states[99].fields[0] = 0;
    initialize_fields(states + 99);
    states[100].fields[0] = (u32)states;
}
#pragma code_seg(".anchor")
void __stdcall compiler_anchor_00404550(State *states) {
    sub_00404550(states);
}
