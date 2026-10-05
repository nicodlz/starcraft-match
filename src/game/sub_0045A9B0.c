/* Actual inputs: DL group, stack BYTE flag; ignored ECX is a C representation. */
typedef unsigned char u8;
typedef unsigned int u32;
extern u8 g_0057EEE4[];
extern u32 g_0057F1EC[];
#pragma code_seg(".group")
void __fastcall sub_0045A9B0(u32 unused,u8 group,u8 enabled) {
 int owner;
 u8 *outer;
 if(group<1 || group>4)return;
 owner=0;
 outer=g_0057EEE4+4;
 do {
  if(outer[2]==group && outer[0]==2) {
   int third=2;
   u8 *inner=g_0057EEE4+4;
   do {
#define UPDATE(n,at) if(owner!=(u32)third+(n) && inner[(at)+2]==group && inner[at]==2) {if(enabled)g_0057F1EC[owner]|=1u<<((u32)third+(n));else g_0057F1EC[owner]&=~(1u<<((u32)third+(n)));}
    UPDATE(-2,0) UPDATE(-1,36) UPDATE(0,72) UPDATE(1,108)
#undef UPDATE
    inner+=144;
    third+=4;
   }while(third<10);
  }
  outer+=36;
  ++owner;
 }while((int)(u32)outer<(int)(u32)(g_0057EEE4+292));
}
