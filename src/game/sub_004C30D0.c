#pragma code_seg(".free")
#include "sub_00410070.c"

#pragma code_seg(".root")
#define D(a) (*(volatile u32 *)(a))
u32 sub_004C30D0(void) {
 u32 result;
 sub_00410070(D(0x006D1250),0x00502AFC,0x3A,0);
 sub_00410070(D(0x006D1254),0x00502AFC,0x3B,0);
 result=sub_00410070(D(0x006D1258),0x00502AFC,0x3C,0);
 D(0x006D1250)=0;D(0x006D1254)=0;D(0x006D1258)=0;
 return result;
}
