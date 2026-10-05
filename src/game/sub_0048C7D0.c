/* Reviewed descending traversal of all 2,000 twenty-byte records. */
typedef unsigned int u32;
typedef unsigned char u8;
extern u8 g_0059CCA8[];
extern u32 g_006416A0[],g_0064B2E0;
#pragma code_seg(".unit")
static u32 pack_unit(u32 pointer) {
 u32 id;
 if(!pointer)return 0;
 id=(pointer-(u32)g_0059CCA8)/336u+1u;
 if(id>1700u)return 0;
 return ((u32)*(u8*)(pointer+165u)<<11)|id;
}
#pragma code_seg(".link")
static u32 pack_link(u32 pointer) {if(!pointer)return 0;return (int)(pointer-(u32)g_006416A0)/20+1;}
#pragma code_seg(".pool")
void sub_0048C7D0(void) {
 u32 cursor=(u32)&g_0064B2E0;
 do {
  u32 unit=*(u32*)(cursor-4u);
  cursor-=20u;
  ((u32*)cursor)[4]=pack_unit(unit);
  ((u32*)cursor)[0]=pack_link(((u32*)cursor)[0]);
  ((u32*)cursor)[1]=pack_link(((u32*)cursor)[1]);
 }while(cursor!=(u32)g_006416A0);
}
