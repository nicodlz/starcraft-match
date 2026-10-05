/* Reclassify existing nodes at the eight signed-byte neighboring offsets. */
void _WriteBarrier(void);
#pragma intrinsic(_WriteBarrier)
__declspec(noinline) unsigned int __stdcall sub_00414290(unsigned int,unsigned int);
#include "sub_00414290.c"
#define SC_NODE_LOOKUP_COMPONENT
#define u32 lookup_u32
#pragma code_seg(".lookup")
#include "sub_0047D2C0.c"
#undef u32
#undef SC_NODE_LOOKUP_COMPONENT
typedef signed char s8;
typedef struct BucketNode { struct BucketNode *next,*previous,*hash_next,*hash_previous;u8 x,y,count,padding;} BucketNode;
typedef char sc_bucket_node_size[(sizeof(BucketNode)==20)?1:-1];
extern u16 g_0057F1D4,g_0057F1D6;
extern u32 *g_006D1260;
extern BucketNode *g_00658AE8[];
extern u16 g_0065EB14[];
#pragma code_seg(".pred")
static u32 tile_matches(u32 x,u32 y) {
 u16 *tile;u32 index,result;
 /* Keep the observed table-base read before its DWORD stride read. */
 tile=(*(u16 *volatile*)0x006D0E84u);
 index=y;index*=(*(volatile u32*)0x006D0F08u);index+=x;
 if((tile[index]&0x7FF0u)==16)result=1;else result=0;
 _WriteBarrier();
 return result;
}
#pragma code_seg(".update")
void __stdcall sub_0047DC10(u32 center_x,u32 center_y) {
 s8 offsets[16];int i;u32 x,y,count,old;BucketNode *node;
 offsets[0]=-1;offsets[1]=-1;offsets[2]=0;offsets[3]=-1;
 offsets[4]=1;offsets[5]=-1;offsets[6]=-1;offsets[7]=0;
 offsets[8]=1;offsets[9]=0;offsets[10]=-1;offsets[11]=1;
 offsets[12]=0;offsets[13]=1;offsets[14]=1;offsets[15]=1;
 for(i=0;i<8;++i) {
  y=center_y+offsets[2*i+1];x=center_x+offsets[2*i];
  if(x<g_0057F1D4 && y<g_0057F1D6 && tile_matches(x,y) && ((u8*)g_006D1260)[4*((u32)g_0057F1D4*y+x)+3]&0x10u) {
   node=(BucketNode*)sub_0047D2C0(y,x);count=sub_00414290(x,y);old=node->count;
   if(count!=old) {
    --g_0065EB14[old];
    if(node==g_00658AE8[old])g_00658AE8[old]=node->next;
    if(node->next)node->next->previous=node->previous;
    if(node->previous)node->previous->next=node->next;
    node->count=(u8)count;node->next=0;node->previous=0;
    count=node->count;
    ++g_0065EB14[count];node->next=g_00658AE8[count];node->previous=0;
    if(g_00658AE8[count])g_00658AE8[count]->previous=node;
    g_00658AE8[count]=node;
   }
  }
 }
}
