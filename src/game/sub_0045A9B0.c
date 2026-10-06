/* Reviewed eight-record DWORD peer-mask update; DL and stack BYTE inputs. */
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
   int peer;
   for(peer=0;peer<8;++peer) {
    if(owner!=peer && g_0057EEE4[6+peer*36]==group && g_0057EEE4[4+peer*36]==2) {
     if(enabled)g_0057F1EC[owner]|=1<<peer;
     else g_0057F1EC[owner]&=~(1<<peer);
    }
   }
  }
  outer+=36;
  ++owner;
 }while((int)(u32)outer<(int)(u32)(g_0057EEE4+292));
}
