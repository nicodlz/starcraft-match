typedef unsigned int U32;
typedef unsigned char U8;
extern U32 sub_0059724C[12];
extern void *memset(void *,int,U32);
extern void *memcpy(void *,const void *,U32);
#pragma intrinsic(memset,memcpy)
extern U32 sub_0059727C;
extern U8 sub_00597280;
extern void __fastcall sub_00485BD0(const void *packet,U32 length);
extern void __fastcall sub_004967E0(U8 slot);
__declspec(dllimport) U32 __stdcall GetTickCount(void);
#pragma code_seg(".scmatch")
static __declspec(noinline) void __stdcall sub_004C07B0(U8 slot,volatile U8 action,const U32 *source,U8 count)
{
 U8 packet[3]; U32 tick;
 packet[0]=19; packet[1]=action; packet[2]=slot;
 sub_00485BD0(packet,3);
 if(action==1) {
 memset(sub_0059724C,0,48);
 memcpy(sub_0059724C,source,(U32)count*4u);
 tick=GetTickCount();
 if(slot==sub_00597280 && tick-sub_0059727C<500u) {
  sub_004967E0(slot); sub_00597280=255;
 } else { sub_00597280=slot; sub_0059727C=tick; }
 } else { sub_00597280=255; }
}
#pragma code_seg(".scctx")
void hypothetical_context(U8 slot,const U32 *source,U8 count)
{
 sub_004C07B0(slot,1,source,count);
 sub_004C07B0(slot,0,source,count);
}
