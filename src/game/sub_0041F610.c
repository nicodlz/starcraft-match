typedef unsigned char u8;
typedef unsigned int u32;
#define CURRENT (*(u32*)0x6ce0c0u)
#define SAVED (*(u32*)0x6ce0e8u)
#pragma code_seg(".root")
__declspec(noinline) static void __stdcall sub_0041F610(u8 value){
 if(value==1){CURRENT=SAVED;return;}
 SAVED=CURRENT;
 switch(value){
 case 2:CURRENT=0x6ce000u;return;
 case 3:CURRENT=0x6ce008u;return;
 case 5:CURRENT=0x6ce018u;return;
 case 4:CURRENT=0x6ce010u;return;
 case 6:CURRENT=0x6ce020u;return;
 case 7:CURRENT=0x6ce028u;return;
 case 8:CURRENT=0x6ce040u;return;
 case 14:CURRENT=0x6ce048u;return;
 case 15:CURRENT=0x6ce050u;return;
 case 16:CURRENT=0x6ce058u;return;
 case 17:CURRENT=0x6ce060u;return;
 case 21:CURRENT=0x6ce068u;return;
 case 22:CURRENT=0x6ce070u;return;
 case 23:CURRENT=0x6ce078u;return;
 case 24:CURRENT=0x6ce080u;return;
 case 25:CURRENT=0x6ce088u;return;
 case 27:CURRENT=0x6ce090u;return;
 case 28:CURRENT=0x6ce098u;return;
 case 29:CURRENT=0x6ce0a0u;return;
 case 30:CURRENT=0x6ce0a8u;return;
 case 31:CURRENT=0x6ce0b8u;return;
 }
}
#pragma code_seg(".context")
void __cdecl context(u8 value){sub_0041F610(value);}
