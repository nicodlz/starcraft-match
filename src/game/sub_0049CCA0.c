static __declspec(noinline) unsigned int sub_0049CCA0(const short *bounds)
{
    if (bounds[0] >= 0 &&
        bounds[2] < *(unsigned short *)0x00628450u &&
        bounds[1] >= 0 &&
        bounds[3] < *(unsigned short *)0x006284B4u - 32) return 1;
    return 0;
}
unsigned int context_0049CCA0(const short *bounds)
{
    return sub_0049CCA0(bounds);
}
