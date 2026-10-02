#if defined(_MSC_VER)
#define FAST __fastcall
#define INLINE __forceinline
#else
#define FAST __attribute__((fastcall))
#define INLINE __attribute__((always_inline)) inline
#endif
typedef unsigned int U32;
typedef struct Entry { U32 next; U32 previous; U32 field[11]; } Entry;
typedef struct Pool { Entry entry[100]; U32 cursor; } Pool;
typedef char EntrySizeCheck[sizeof(Entry) == 52 ? 1 : -1];
typedef char PoolSizeCheck[sizeof(Pool) == 5204 ? 1 : -1];
static INLINE void clear_fields(Entry *p)
{
    p->field[0]=0; p->field[1]=0; p->field[2]=0; p->field[3]=0;
    p->field[5]=0; p->field[4]=0; p->field[6]=0; p->field[7]=0;
    p->field[8]=0; p->field[9]=0; p->field[10]=0;
}
void FAST sub_00403130(unsigned unused, Pool *pool)
{
    Entry *first, *second;
    U32 cursor;
    unsigned remaining = 49;
    pool->entry[0].next = (U32)&pool->entry[1];
    pool->entry[0].previous = 0;
    clear_fields(&pool->entry[0]);
    cursor = (U32)&pool->entry[2].field[1];
    do {
        *(volatile U32 *)(cursor - 60u) = (U32)(cursor - 116u);
        first = (Entry *)(cursor - 64u);
        second = (Entry *)(cursor - 12u);
        *(volatile U32 *)first = (U32)second;
        *(volatile U32 *)(cursor - 56u) = 0;
        *(volatile U32 *)(cursor - 52u) = 0;
        *(volatile U32 *)(cursor - 48u) = 0;
        *(volatile U32 *)(cursor - 44u) = 0;
        *(volatile U32 *)(cursor - 36u) = 0;
        *(volatile U32 *)(cursor - 40u) = 0;
        *(volatile U32 *)(cursor - 32u) = 0;
        *(volatile U32 *)(cursor - 28u) = 0;
        *(volatile U32 *)(cursor - 24u) = 0;
        *(volatile U32 *)(cursor - 20u) = 0;
        *(volatile U32 *)(cursor - 16u) = 0;
        *(volatile U32 *)(cursor - 8u) = (U32)first;
        first = (Entry *)(cursor + 40u);
        *(volatile U32 *)second = (U32)first;
        *(volatile U32 *)(cursor - 4u) = 0;
        *(volatile U32 *)(cursor + 0u) = 0;
        *(volatile U32 *)(cursor + 4u) = 0;
        *(volatile U32 *)(cursor + 8u) = 0;
        *(volatile U32 *)(cursor + 16u) = 0;
        *(volatile U32 *)(cursor + 12u) = 0;
        *(volatile U32 *)(cursor + 20u) = 0;
        *(volatile U32 *)(cursor + 24u) = 0;
        *(volatile U32 *)(cursor + 28u) = 0;
        *(volatile U32 *)(cursor + 32u) = 0;
        *(volatile U32 *)(cursor + 36u) = 0;
        cursor += 104u;
    } while (--remaining);
    pool->entry[99].next = 0;
    pool->entry[99].previous = (U32)&pool->entry[98];
    clear_fields(&pool->entry[99]);
    pool->cursor = (U32)&pool->entry[0];
}
