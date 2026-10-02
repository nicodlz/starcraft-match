typedef unsigned short u16;
typedef unsigned long u32;
static __declspec(noinline) void sub_0044E420(const u16 *src, u16 *dest)
{
    dest[0]=src[0]; dest[1]=src[1]; dest[2]=src[2]; dest[3]=src[3];
    dest[4]=src[4]; dest[5]=src[5]; dest[6]=src[6]; dest[7]=src[7];
    {
    u32 index = 0;
    u32 remaining = 44;
    do {
        u32 next;
        u32 current;
        u16 a,b;
        ++index;
        next = (index + 1) & 7;
        a = dest[next];
        current = index & 7;
        b = dest[current];
        dest[index + 7] = (u16)((a >> 7) | (u16)(b << 9));
        dest += index & 8;
        index = current;
    } while (--remaining);
    }
}
void context_0044E420(u16 *dest,const u16 *src) { sub_0044E420(src,dest); }
