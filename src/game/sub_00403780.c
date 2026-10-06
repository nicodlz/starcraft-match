/* Restore fixed-width references in the reviewed 1,000-entry pool. */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct Entry {
    u32 next, previous;
    u8 bytes[4];
    u32 unit, path;
} Entry;
typedef char sc_observed_entry_size[(sizeof(Entry) == 20) ? 1 : -1];
typedef struct Unit {u8 bytes[336];} Unit;
extern Unit g_0059CCA8[];

#pragma code_seg(".uunit")
static u32 decode_unit(u32 id)
{
    return id ? (u32)&g_0059CCA8[(id & 0x7FFu) - 1] : 0;
}
#pragma code_seg(".hlist")
static u32 decode_path(u32 id)
{
    u8 pool;
    u32 index;
    unsigned char *base;
    if (!id) return 0;
    pool = (u8)(id / 2500u);
    index = id - pool * 2500u;
    if (pool >= 8) return 0;
    base = ((unsigned char **)0x0069A604u)[pool];
    if (!base || !index || index > (u32)**(short **)0x006D5BFCu) return 0;
    return (u32)(base + index * 52 - 52);
}
#pragma code_seg(".helpers")
static u32 decode_link(u32 id, Entry *entries)
{
    if (!id) return 0;
    return (u32)(entries + id - 1);
}
#pragma code_seg(".restore")
void __stdcall sub_00403780(Entry *entries)
{
    volatile u32 i = 0;
    u32 next;
    do {
        Entry *entry = entries + i;
        {
            Entry *current = entry + 0;
            current->unit = decode_unit(current->unit);
            current->path = current->unit ? decode_path(current->path) : 0;
            entry[0].next = decode_link(entry[0].next, entries);
            entry[0].previous = decode_link(entry[0].previous, entries);
        }
        {
            Entry *current = entry + 1;
            current->unit = decode_unit(current->unit);
            current->path = current->unit ? decode_path(current->path) : 0;
            entry[1].next = decode_link(entry[1].next, entries);
            entry[1].previous = decode_link(entry[1].previous, entries);
        }
        {
            u32 snapshot = i;
            Entry *current = (Entry *)((u32 *)entries + snapshot * 5u + 10u);
            current->unit = decode_unit(current->unit);
            current->path = current->unit ? decode_path(current->path) : 0;
            current->next = decode_link(current->next, entries);
            entry[2].previous = decode_link(entry[2].previous, entries);
        }
        {
            u32 snapshot = i;
            Entry *current = (Entry *)((u32 *)entries + snapshot * 5u + 15u);
            current->unit = decode_unit(current->unit);
            current->path = current->unit ? decode_path(current->path) : 0;
            current->next = decode_link(current->next, entries);
            entry[3].previous = decode_link(entry[3].previous, entries);
        }
        {
            u32 snapshot = i;
            Entry *current = (Entry *)((u32 *)entries + snapshot * 5u + 20u);
            current->unit = decode_unit(current->unit);
            current->path = current->unit ? decode_path(current->path) : 0;
            current->next = decode_link(current->next, entries);
            entry[4].previous = decode_link(entry[4].previous, entries);
        }
        next = i + 5;
        i = next;
    } while (next < 1000);
    {
        u32 id = *(u32 *)(entries + 1000);
        if (!id) {
            *(u32 *)(entries + 1000) = 0;
            return;
        }
        *(u32 *)(entries + 1000) = (u32)(entries + id - 1);
    }
}
