/* Serialize the reviewed 100-record pool using its actual C encoder. */
#define SC_STATE_COMPONENT 1
#include "sub_00403AE0.c"
void *__cdecl memset(void *, int, u32);
#pragma intrinsic(memset)
#pragma code_seg(".ulink")
static u32 encode_link(u32 pointer, State *states) {
    if (!pointer) return 0;
    return (pointer - (u32)states) / 460u + 1;
}
#pragma code_seg(".pack")
__declspec(noinline) static void __fastcall sub_00404620(State *states) {
    State *state = (State *)states[100].fields[0];
    u32 n;
    while (state) {
        memset(&state->fields[6], 0, 436u);
        state = (State *)state->fields[0];
    }
    for (state = states, n = 100; n; --n, ++state) {
        sub_00403AE0(state);
        state->fields[0] = encode_link(state->fields[0], states);
        state->fields[1] = encode_link(state->fields[1], states);
    }
    states[100].fields[0] = encode_link(states[100].fields[0], states);
}
#pragma code_seg(".anchor")
void __stdcall compiler_anchor_00404620(State *states) {
    sub_00404620(states);
}
