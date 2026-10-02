typedef unsigned long u32;
static __declspec(noinline) void sub_0047D400(u32 *p)
{
    u32 value=p[0];
    if (value) value=value*20+0x00659AFC;
    p[0]=value;
    value=p[1];
    if (value) value=value*20+0x00659AFC;
    p[1]=value;
    value=p[2];
    if (value) value=value*20+0x00659AFC;
    p[2]=value;
    value=p[3];
    if (!value) { *(volatile u32 *)(p+3)=value; return; }
    value=value*20+0x00659AFC;
    *(volatile u32 *)(p+3)=value;
}
void experiment_0047D400(u32 *p) { sub_0047D400(p); }
