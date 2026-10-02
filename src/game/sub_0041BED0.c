#ifdef _MSC_VER
#define SC_NOINLINE __declspec(noinline)
#else
#define SC_NOINLINE __attribute__((noinline))
#endif
struct Bounds { short left, top, right, bottom; };
static SC_NOINLINE int sub_0041BED0(const struct Bounds *r)
{
    int x = *(short *)0x006CEF52;
    int y = *(short *)0x006CEF54;
    int w = *(short *)0x006CEF56;
    if (x+w-1 < r->left || x > r->right) return 0;
    if (y+*(short *)0x006CEF58-1 < r->top || y > r->bottom) return 0;
    return 1;
}
int context_0041BED0(const struct Bounds *r) { return sub_0041BED0(r); }
