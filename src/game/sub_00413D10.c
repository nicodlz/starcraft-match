#if defined(_MSC_VER)
#define SC_STDCALL __stdcall
#define SC_NOINLINE __declspec(noinline)
#else
#define SC_STDCALL __attribute__((stdcall))
#define SC_NOINLINE __attribute__((noinline))
#endif
typedef unsigned int u32;
struct Rectangle00413D10 { int left, top, right, bottom; };
typedef int (SC_STDCALL *Callback00413D10)(u32,u32,struct Rectangle00413D10 *);
static SC_NOINLINE int SC_STDCALL sub_00413D10(u32 x, u32 y, Callback00413D10 callback)
{
    struct Rectangle00413D10 rectangle;
    u32 centerx = (x << 5) + 16;
    u32 centery = (y << 5) + 16;
    int left = (int)(centerx - 640);
    int top = (int)(centery - 400);
    int right = (int)(centerx + 640);
    int bottom = (int)(centery + 400);
    rectangle.left = left;
    rectangle.right = right;
    rectangle.top = top;
    rectangle.bottom = bottom;
    if (left < 0) rectangle.left = 0;
    else {
        int limit = (int)(*(u32 *)0x006D0F08 << 5);
        if (right >= limit) rectangle.right = (int)((u32)limit - 1);
    }
    if (top < 0) {
        rectangle.top = 0;
    } else {
        int limit = (int)(*(u32 *)0x006D0C6C << 5);
        if (bottom >= limit) rectangle.bottom = (int)((u32)limit - 1);
    }
    return callback(x,y,&rectangle);
}
/* Independent optimization context only. */
int context_00413D10(u32 x,u32 y,Callback00413D10 callback)
{
    return sub_00413D10(x,y,callback);
}
