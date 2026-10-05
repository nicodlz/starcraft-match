/* Initialize the reviewed 1,000-entry pool and its free-list head. */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct Entry {
    struct Entry *next, *previous;
    u8 a, b;
    unsigned short c;
    u32 unit, path;
} Entry;
typedef char sc_entry_size[(sizeof(Entry) == 20) ? 1 : -1];
void __fastcall sub_00403650(Entry *entries) {
    u32 i;
    Entry *last;
    entries[0].next = entries + 1;
    entries[0].previous = 0;
    entries[0].a = 0;
    entries[0].unit = 0;
    entries[0].path = 0;
    entries[0].c = 0;
    entries[0].b = 0;
    for (i = 1; i < 999; ++i) {
        Entry *entry = entries + i;
        entry->previous = entry - 1;
        entry->next = entry + 1;
        entry->a = 0;
        entry->unit = 0;
        entry->path = 0;
        entry->c = 0;
        entry->b = 0;
    }
    last = entries + 999;
    last->next = 0;
    last->previous = last - 1;
    entries[999].a = 0;
    entries[999].unit = 0;
    entries[999].path = 0;
    entries[999].c = 0;
    entries[999].b = 0;
    *(Entry **)(entries + 1000) = entries;
}
