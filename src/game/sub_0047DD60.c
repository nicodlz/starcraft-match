/* Reviewed private ABI: x on stack, y in preserved EBX, RET4. */
__declspec(noinline) unsigned int __stdcall sub_00414290(unsigned int, unsigned int);
#include "sub_00414290.c"
struct HashNode;
__declspec(noinline) unsigned long __fastcall sub_0047D5F0(struct HashNode *);
#define Node HashNode
#pragma code_seg(".hash")
#include "sub_0047D5F0.c"
#undef Node
typedef unsigned char u8;
typedef struct BucketNode {
 struct BucketNode *next, *previous;
 struct BucketNode *hash_next, *hash_previous;
 u8 x, y, count, padding;
} BucketNode;
extern BucketNode * g_00658AE8[];
extern u16 g_0065EB14[];
extern u16 g_0065EB26;
extern BucketNode *g_00658B0C;
extern u16 g_0057F1D4;
extern u32 *g_006D1260;
#pragma code_seg(".move")
__declspec(noinline) static u32 __stdcall sub_0047DD60(u32 x, u32 y) {
 BucketNode *node;
 u32 count;
 if (!g_0065EB26) return 0;
 node = g_00658B0C;
 count = node->count;
 --g_0065EB14[count];
 if (node == g_00658AE8[count]) g_00658AE8[count] = node->next;
 if (node->next) node->next->previous = node->previous;
 if (node->previous) node->previous->next = node->next;
 node->next = 0; node->previous = 0;
 node->x = (u8)x; node->y = (u8)y;
 node->count = (u8)sub_00414290(x,y);
 count = node->count;
 ++g_0065EB14[count];
 node->next = g_00658AE8[count];
 node->previous = 0;
 if (g_00658AE8[count]) g_00658AE8[count]->previous = node;
 g_00658AE8[count] = node;
 sub_0047D5F0((HashNode *)node);
 g_006D1260[(u32)g_0057F1D4 * y + x] |= 0x10000000u;
 return 1;
}
#pragma code_seg(".anchor")
u32 __stdcall compiler_anchor_0047DD60(u32 x, u32 y) {return sub_0047DD60(x,y);}
