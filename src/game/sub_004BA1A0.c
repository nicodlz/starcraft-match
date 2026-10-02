#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned char U8;
typedef unsigned int U32;
extern void STDCALL sub_00410070(U32 allocation, const char *file, U32 line, U32 flags);
#pragma code_seg(".scmatch")
#if defined(_MSC_VER)
#define INLINE __forceinline
#else
#define INLINE __attribute__((always_inline)) inline
#endif
#pragma code_seg(".scctx")
static INLINE U8 *lookup_004BA1A0(U8 *object, unsigned short id)
{
    U8 *node;
    if (*(unsigned short *)(object+0x22)) object=*(U8 **)(object+0x32);
    node=*(U8 **)(object+0x42);
    while (node) {
        if (*(unsigned short *)(node+0x20)==id) return node;
        node=*(U8 **)node;
    }
    return 0;
}
#pragma code_seg(".scmatch")
static NOINLINE void sub_004BA1A0(unsigned short id, U8 *object)
{
    U8 *node=lookup_004BA1A0(object,id);
    sub_00410070(*(U32 *)(node+0x14),(const char *)0x00502d6c,0x207,0);
    *(U32 *)(node+0x14)=0;
}
#pragma code_seg(".scctx2")
/* Hypothetical C compiler context; not reconstructed or counted. */
void context_004BA1A0(unsigned short id, U8 *object) { sub_004BA1A0(id,object); }
