#ifdef _MSC_VER
#define SC_NOINLINE __declspec(noinline)
#define SC_INLINE __forceinline
#else
#define SC_NOINLINE __attribute__((noinline))
#define SC_INLINE __attribute__((always_inline)) __inline__
#endif
struct State { unsigned int a,b,c,d; unsigned short e,f,g,h; };
struct Node { struct State state; unsigned char gap1[16]; unsigned short x,y,z,w; unsigned char gap2[324]; struct State saved; };
typedef char state_size_is_24[(sizeof(struct State)==24)?1:-1];
typedef char node_size_is_396[(sizeof(struct Node)==396)?1:-1];
static SC_NOINLINE void sub_00421BA0(struct Node *d, const struct Node *s)
{
    d->saved.a=s->state.a;
    d->saved.b=s->state.b;
    d->saved.c=s->state.c;
    d->saved.d=s->state.d;
    d->saved.e=s->state.e;
    d->saved.f=s->state.f;
    d->saved.g=s->state.g;
    d->saved.h=s->state.h;
    d->x=s->x; d->y=s->y; d->z=s->z; d->w=s->w;
    d->state.a=d->saved.a;
    d->state.b=d->saved.b;
    d->state.c=d->saved.c;
    d->state.d=d->saved.d;
    d->state.e=d->saved.e;
    d->state.f=d->saved.f;
    d->state.g=d->saved.g;
    d->state.h=d->saved.h;
}
void context_00421BA0(struct Node *d, const struct Node *s) { sub_00421BA0(d,s); }
