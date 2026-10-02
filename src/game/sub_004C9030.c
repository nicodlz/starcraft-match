typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;
struct object { u8 pad[20]; char *text; };
static __forceinline char *lookup(u32 index)
{
    u16 *p = *(u16 **)0x006d1220;
    if (*p <= index - 1)
        return (char *)0x00501b7d;
    return (char *)p + p[index];
}
static __declspec(noinline) void sub_004C9030(struct object *p)
{
    switch (*(u32 *)0x00596869) {
    case 2500: p->text = lookup(118); break;
    case 5000: p->text = lookup(119); break;
    case 7500: p->text = lookup(120); break;
    case 10000: p->text = lookup(121); break;
    }
}
void context_004C9030(struct object *p)
{
    sub_004C9030(p);
}
