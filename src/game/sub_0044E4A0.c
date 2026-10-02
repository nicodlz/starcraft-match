static __declspec(noinline) unsigned int sub_0044E4A0(unsigned int x)
{
    unsigned int r, q, b, t;
    if (x <= 1) return x;
    q = 65537u / x;
    r = 65537u % x;
    if (r == 1) return (r - q) & 65535u;
    b = 1;
    do {
        t = x / r;
        x %= r;
        b += t * q;
        if (x == 1) return b;
        t = r / x;
        r %= x;
        q += t * b;
    } while (r != 1);
    return (r - q) & 65535u;
}
unsigned int context_0044E4A0(unsigned int x)
{
    return sub_0044E4A0(x);
}
