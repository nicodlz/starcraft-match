#if defined(_MSC_VER)
#define SC_STATIC static __declspec(noinline)
#else
#define SC_STATIC static __attribute__((noinline))
#endif
/* The static leaf acquires EAX/ECX inputs under the recorded MSVC profile. */
typedef char WordWidth0041BF60[(sizeof(short) == 2) ? 1 : -1];

SC_STATIC unsigned sub_0041BF60(short *out, const volatile short *bounds)
{
    short edge;
    edge=bounds[0]; if (out[0]<edge) out[0]=edge;
    edge=bounds[2]; if (out[2]>edge) out[2]=edge;
    edge=bounds[1]; if (out[1]<edge) out[1]=edge;
    edge=bounds[3]; if (out[3]>edge) out[3]=edge;
    edge=out[1];
    if (edge>out[3]) return 1;
    edge=out[0];
    return edge>out[2];
}
/* Ordinary C caller shapes compilation; it is not a reconstructed game entry. */
unsigned probe_0041BF60(short *out,const volatile short *bounds)
{
    return sub_0041BF60(out,bounds);
}
