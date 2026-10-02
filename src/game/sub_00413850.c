#ifdef _MSC_VER
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
typedef unsigned int u32;
static NOINLINE int sub_00413850(u32 y, u32 x)
{
    return (int)(x*x*256u + y*y*100u) > 10240000;
}
int context_00413850(u32 x,u32 y) { return sub_00413850(y,x); }
