#if defined(_MSC_VER) && !defined(__clang__)
#define SC_LOCAL static __declspec(noinline)
void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)
#else
#define SC_LOCAL static __attribute__((noinline))
static __attribute__((always_inline)) inline void sc_clear_00497C30(void) {
    unsigned int i;
    for(i=0;i<64;++i) ((volatile unsigned int *)0x0063FD30u)[i]=0;
}
#endif
typedef char sc_dword_width[(sizeof(unsigned int)==4)?1:-1];

/* Observed EBX index, unsigned wrap and unguarded object-list walk. */
SC_LOCAL void sub_00497C30(unsigned int start) {
    unsigned int offset;
    unsigned char *slot;
    unsigned int end;
    unsigned int hash;
    unsigned int index;
#if defined(_MSC_VER) && !defined(__clang__)
    memset((void *)0x0063FD30u,0,256);
#else
    sc_clear_00497C30();
#endif
    slot = (unsigned char *)0x0063FD30u;
    offset = 0;
    do {
        const unsigned char *object = *(const unsigned char *const *)(0x00629688u+offset);
        while(object!=0) {
            if (((const unsigned char *)0x00629A88u)[*(const unsigned short *)(object+8)] != 0) *slot ^= object[0xC];
            object = *(const unsigned char *const *)(object+4);
        }
        offset += 4;
        ++slot;
    } while(offset < 0x400);
    end = start + 13;
    if(end >= 256) end = 255;
    hash = 0;
    index = start;
    if(index <= end) do {
        hash ^= ((const unsigned char *)0x00629C90u)[index];
        hash = (hash << 1) | (hash >> 31);
        ++index;
    } while(index <= end);
    hash ^= hash >> 16;
    *(unsigned char *)0x0063FE38u = (unsigned char)(hash ^ (hash >> 8));
    *(unsigned int *)0x0063FD28u = start;
}
/* Independent compiler context only; not matched, counted or claimed linked. */
void sc_compile_context_00497C30(unsigned int start) { sub_00497C30(start); }
