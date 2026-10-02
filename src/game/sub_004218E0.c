typedef unsigned long u32;
typedef struct Pair {u32 a;u32 b;} Pair;
typedef struct Dest {unsigned char pad[0x18c];short count;short pad2;Pair values[1];} Dest;
static __declspec(noinline) void sub_004218E0(Dest *dest, const Pair *src)
{
 dest->values[dest->count]=*src;
 ++dest->count;
}
void context_004218E0(Dest *dest,const Pair *src){sub_004218E0(dest,src);}
