#if defined(_MSC_VER)
#define PRIVATE static __declspec(noinline)
#else
#define PRIVATE static __attribute__((noinline))
#endif
PRIVATE int sub_0041BE70(const short *r)
{
 int x=*(const short *)0x006cef66;
 int y=*(const short *)0x006cef68;
 int width=*(const short *)0x006cef6a;
 if (x+width-1 >= r[0] && x <= r[2] &&
     y+*(const short *)0x006cef6c-1 >= r[1] && y <= r[3]) return 1;
 return 0;
}
int context_0041BE70(const short *r) { return sub_0041BE70(r); }
