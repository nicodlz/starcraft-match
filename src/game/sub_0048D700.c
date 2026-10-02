typedef unsigned int u32;
typedef unsigned short u16;
#pragma pack(push,2)
struct Record0048D700 {
    u16 previous : 16;
    u16 a;
    u16 b;
    u16 c;
    u16 unused;
    u32 associated;
    u32 callback;
    u16 tail;
};
#pragma pack(pop)
typedef char record_size[(sizeof(struct Record0048D700)==20)?1:-1];
void sub_0048D700(void)
{
    struct Record0048D700 *p = (struct Record0048D700 *)0x006CEF8Eu;
    u32 cursor;
    *(u32 *)0x00640884u = 0;
    *(u32 *)0x00640880u = 0;
    *(unsigned char *)0x0064088Cu = 255;
    for (cursor = 0x0064095Cu; (int)cursor < 0x0064096C; cursor += 8u) {
        p->associated = cursor;
        p->previous = 0;
        p->a = 0;
        p->b = 0;
        p->c = 0;
        p->callback = 0x0048D5C0u;
        *((unsigned char *)p-1) = 0;
        ++p;
    }
}
