/* Restore fixed-width references in the reviewed 1,000-entry pool. */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct Entry {
    u32 next, previous;
    u8 bytes[4];
    u32 unit, path;
} Entry;
typedef char sc_observed_entry_size[(sizeof(Entry) == 20) ? 1 : -1];
static u32 decode_unit(u32 id)
{
    return id ? (u32)((unsigned char *)0x0059CB58u + (id & 0x7FFu) * 0x150u) : 0;
}
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
static u32 decode_link(u32 id, Entry *entries)
{
    if (id) id = (u32)(entries + id - 1);
    return id;
}
void __stdcall sub_00403780(Entry *entries)
{
    u32 i;
    for (i = 0; i < 1000; ++i) {
        Entry *entry = entries + i;
        entry->unit = decode_unit(entry->unit);
        entry->path = entry->unit ? decode_path(entry->path) : 0;
        entry->next = decode_link(entry->next, entries);
        entry->previous = decode_link(entry->previous, entries);
    }
    *(u32 *)(entries + 1000) = decode_link(*(u32 *)(entries + 1000), entries);
}
