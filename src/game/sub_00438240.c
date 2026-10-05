/* Encode unit/path references with the observed unsigned arithmetic. */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct Entry {
    u32 next, previous;
    u8 byte8, byte9;
    unsigned short word10;
    u32 unit, path;
} Entry;
typedef char sc_entry_size[(sizeof(Entry) == 20) ? 1 : -1];
extern u8 g_0059CCA8[];
#pragma code_seg(".uunit")
static u32 encode_unit(u32 unit) {
    u32 id;
    if (!unit) return 0;
    id = (unit - (u32)g_0059CCA8) / 336u + 1;
    if (id > 1700) return 0;
    return ((u32)*(u8 *)(unit + 165) << 11) | id;
}
#pragma code_seg(".upath")
static u32 encode_path(u32 path) {
    u8 pool;
    u32 id;
    if (!path) return 0;
    pool = *(u8 *)(path + 4);
    id = (path - ((u32 *)0x0069A604u)[pool]) / 52u;
    if (id >= (u32)**(short **)0x006D5BFCu) return 0;
    return pool * 2500u + id + 1;
}
#pragma code_seg(".encode")
__declspec(noinline) static void __fastcall sub_00438240(Entry *entry) {
    entry->unit = encode_unit(entry->unit);
    entry->path = encode_path(entry->path);
}

#ifndef SC_PATHING_COMPONENT
#pragma code_seg(".anchor")
void __stdcall compiler_anchor_00438240(Entry *entries) {
    Entry *entry;
    u32 n;
    for (entry = entries, n = 1000; n; --n, ++entry) {
        sub_00438240(entry);
        entry->next=entry->next ? (entry->next-(u32)entries)/20u+1 : 0;
        entry->previous=entry->previous ? (entry->previous-(u32)entries)/20u+1 : 0;
    }
    entries[1000].next=entries[1000].next ? (entries[1000].next-(u32)entries)/20u+1 : 0;
}

#endif
