/* Serialize the reviewed 1,000-entry pool and its free-list head. */
#define SC_PATHING_COMPONENT 1
#include "sub_00438240.c"

#pragma code_seg(".ulink")
static u32 encode_link(u32 id, Entry *entries) {
    if (!id) return 0;
    return (id - (u32)entries) / 20u + 1;
}
#pragma code_seg(".pack")
__declspec(noinline) static void __fastcall sub_004036D0(Entry *entries) {
    Entry *entry = (Entry *)entries[1000].next;
    u32 n;
    while (entry) {
        entry->byte8 = 0;
        entry->unit = 0;
        entry->path = 0;
        entry->word10 = 0;
        entry->byte9 = 0;
        entry = (Entry *)entry->next;
    }
    for (entry = entries, n = 1000; n; --n, ++entry) {
        sub_00438240(entry);
        entry->next = encode_link(entry->next, entries);
        entry->previous = encode_link(entry->previous, entries);
    }
    entries[1000].next = encode_link(entries[1000].next, entries);
}
#pragma code_seg(".anchor")
void __stdcall compiler_anchor_004036D0(Entry *entries) {
    sub_004036D0(entries);
}
