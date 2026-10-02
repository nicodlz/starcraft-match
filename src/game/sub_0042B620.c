typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
typedef struct Group { U8 a, pad_a, b, pad_b, c, pad_c; U16 high; } Group;
typedef struct Record { Group g[4]; } Record;
typedef char check_group[sizeof(Group) == 8 ? 1 : -1];
typedef char check_record[sizeof(Record) == 32 ? 1 : -1];
typedef char check_dword[sizeof(U32) == 4 ? 1 : -1];
extern U16 data_005998E0;
extern Record *data_005993D0;
extern void * __stdcall sub_0041006A(U32, const char *, U32, U32);
U32 *sub_0042B620(void)
{
    U32 *allocation = (U32 *)sub_0041006A((U32)data_005998E0 << 4, (const char *)0x005056A4, 0x30F, 0);
    int remaining = data_005998E0;
    Record *record = data_005993D0;
    U32 *out = allocation;
    if (remaining > 0) {
        do {
            U32 t;
            t = (record->g[0].c & 1u) | ((U32)record->g[0].high << 8);
            t = (record->g[0].b & 1u) | (t << 8);
            t = (record->g[0].a & 1u) | (t << 8);
            *out++ = (t ^ 0xFF010101u) << 7;
            t = (record->g[1].c & 1u) | ((U32)record->g[1].high << 8);
            t = (record->g[1].b & 1u) | (t << 8);
            t = (record->g[1].a & 1u) | (t << 8);
            *out++ = (t ^ 0xFF010101u) << 7;
            t = (record->g[2].c & 1u) | ((U32)record->g[2].high << 8);
            t = (record->g[2].b & 1u) | (t << 8);
            t = (record->g[2].a & 1u) | (t << 8);
            *out++ = (t ^ 0xFF010101u) << 7;
            t = (record->g[3].c & 1u) | ((U32)record->g[3].high << 8);
            t = (record->g[3].b & 1u) | (t << 8);
            t = (record->g[3].a & 1u) | (t << 8);
            *out++ = (t ^ 0xFF010101u) << 7;
            ++record;
        } while (--remaining);
    }
    return allocation;
}
