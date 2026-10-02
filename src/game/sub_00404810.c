#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
#define SC_FASTCALL __fastcall
#else
#define SC_NOINLINE __attribute__((noinline))
#define SC_FASTCALL __attribute__((fastcall))
#endif
typedef unsigned short u16;
typedef short s16;
struct Sprite00404810 { unsigned char pad[0x14]; s16 x,y; };
struct Unit00404810 { unsigned char pad[0xC]; struct Sprite00404810 *sprite; unsigned char pad2[0x54]; u16 id; };
struct Bounds00404810 { s16 left,top,right,bottom; };
static SC_NOINLINE void SC_FASTCALL sub_00404810(const struct Unit00404810 *a,const struct Unit00404810 *b, struct Bounds00404810 *out)
{
    s16 y=a->sprite->y;
    s16 x=a->sprite->x;
    const struct Bounds00404810 *bounds=(const struct Bounds00404810 *)0x006617C8+a->id;
    out->top=(s16)(y-bounds->top);
    out->bottom=(s16)(bounds->bottom+y);
    out->left=(s16)(x-bounds->left);
    out->right=(s16)(bounds->right+x);
    out->left=(s16)(out->left-1-((const struct Bounds00404810 *)0x006617C8)[b->id].right);
    out->right=(s16)(out->right+((const struct Bounds00404810 *)0x006617C8)[b->id].left+1);
    out->top=(s16)(out->top-1-((const struct Bounds00404810 *)0x006617C8)[b->id].bottom);
    out->bottom=(s16)(out->bottom+((const struct Bounds00404810 *)0x006617C8)[b->id].top+1);
}
void context_00404810(const struct Unit00404810 *a,const struct Unit00404810 *b,struct Bounds00404810 *out)
{
    sub_00404810(a,b,out);
}
