/* Complete descending restoration of 2,000 records with DWORD wrapping. */
typedef unsigned int u32;
typedef struct Unit {unsigned char opaque[336];} Unit;
typedef char sc_dword_width[(sizeof(u32)==4)?1:-1];
typedef char sc_unit_stride[(sizeof(Unit)==336)?1:-1];
extern Unit g_0059CCA8[];
extern u32 g_006416A0[];

#pragma code_seg(".link")
static u32 unpack_link(u32 value) {
 if(!value)return 0;
 return (u32)g_006416A0-20u+value*20u;
}

#pragma code_seg(".pool")
void sub_0048C770(void) {
 u32 index=10000;
 do {
  u32 value=g_006416A0[index-1];
  index-=5;
  g_006416A0[index+4]=value?(u32)&g_0059CCA8[(value&0x7FFu)-1u]:0;
  value=g_006416A0[index];
  if(value)value=(u32)g_006416A0-20u+value*20u;
  g_006416A0[index]=value;
  value=unpack_link(g_006416A0[index+1]);
  g_006416A0[index+1]=value;
 }while(index!=0);
}
