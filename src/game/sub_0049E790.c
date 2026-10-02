typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void *__stdcall sub_0041006A(u32 bytes, const void *description, u32 line, u32 flags);
extern void __stdcall sub_00410070(void *buffer, const void *description, u32 line, u32 flags);
extern int __stdcall sub_004C3280(void *buffer, u32 bytes, void *stream);
extern void *__cdecl memset(void *buffer, int value, u32 bytes);
extern void *__cdecl memcpy(void *destination, const void *source, u32 bytes);

int __stdcall sub_0049E790(void *stream, u32 count)
{
    u32 bytes;
    u32 offset;
    u32 remaining;
    u8 *buffer;
    u8 *cursor;
    u8 *unit;
    if (count) {
        bytes = count * 324u;
        buffer = (u8 *)sub_0041006A(bytes, (const void *)0x005040F0u, 0x7B5u, 0);
        cursor = buffer;
        if (_MSC_VER == 1310) {
            memset(cursor, 0, bytes);
        } else {
            u32 i;
            for (i = 0; i < (bytes >> 2); ++i)
                ((volatile u32 *)cursor)[i] = 0;
        }
        if (!sub_004C3280(cursor, bytes, stream)) {
            sub_00410070(buffer, (const void *)0x005040F0u, 0x7BBu, 0);
            return 0;
        }
        if (count > 0) {
            remaining = count;
            do {
                offset = *(u32 *)cursor * 336u;
                cursor += 4;
                unit = (u8 *)((unsigned long)0x0059CCA8u + offset);
                if (_MSC_VER == 1310) {
                    memcpy(unit, cursor, 292u);
                } else {
                    u32 i;
                    for (i = 0; i < 73u; ++i)
                        ((volatile u32 *)unit)[i] = ((volatile u32 *)cursor)[i];
                }
                cursor += 292;
                if (_MSC_VER == 1310) {
                    memcpy(unit + 308, cursor, 28u);
                } else {
                    u32 i;
                    for (i = 0; i < 7u; ++i)
                        ((volatile u32 *)(unit + 308))[i] = ((volatile u32 *)cursor)[i];
                }
                cursor += 28;
                if (*(u8 *)((unsigned long)0x00664080u + *(u16 *)(unit + 100) * 4u) & 1u) {
                    if (unit[200] == 24) unit[200] = 44;
                    if (unit[201] == 46) unit[201] = 61;
                }
            } while (--remaining);
        }
        sub_00410070(buffer, (const void *)0x005040F0u, 0x7E1u, 0);
    }
    return 1;
}
