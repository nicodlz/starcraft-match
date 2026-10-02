#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
typedef unsigned int U32;
typedef unsigned char U8;
extern U8 sub_006CE2A0[];
/* Overlapping destination view, actual table base + one DWORD. */
extern U32 sub_006CE324[];
extern void *sub_00408FD0(void *destination,const void *source,U32 bytes);
#if defined(_MSC_VER)
#pragma code_seg(".scmatch")
#endif
static NOINLINE void sub_0041E4B0(U32 index)
{
    U8 *record=sub_006CE2A0+(index<<4);
    U8 first=record[3];
    U32 last=record[5];
    U32 *array=(U32 *)0x006ce320;
    U32 saved=array[last];
    sub_00408FD0(sub_006CE324+first,array+first,(last-first)*4u);
    array[first]=saved;
}
#if defined(_MSC_VER)
#pragma code_seg(".scctx")
#endif
/* Ordinary compiler context only; uncounted. */
void context_0041E4B0(U32 index) { sub_0041E4B0(index); }
