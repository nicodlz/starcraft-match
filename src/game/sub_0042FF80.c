#define SC_FINDER_COMPONENT 1
#pragma code_seg(".find")
#include "sub_00469B00.c"
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct QueryUnit {u8 pad[324];int lower,upper;u8 tail[4];} QueryUnit;
extern u32 g_006BEE64,g_006BEE6C,g_006D63EC,g_0066FF74;
extern u32 g_006BEE70[],g_006BD3D0[],g_0066FF78[],g_006769B8[];
extern QueryUnit *g_006BB938[];
extern QueryUnit g_0059CB58[];
extern int g_0059CCA0[];
#pragma code_seg(".query")
__declspec(noinline) static QueryUnit **__fastcall sub_0042FF80(short *rect) {
 QueryUnit **start,**out;
 int y0,y1,right,bottom;
 u32 x0,count;
 g_006BEE70[g_006BEE6C]=g_006BEE64;
 start=g_006BB938+g_006BEE64;
 out=start;
 ++g_006BEE6C;
 if(++g_006D63EC==0)g_006D63EC=1;
 right=rect[2];bottom=rect[3];
 y0=sub_00469B00(g_006769B8,1,(u32)(int)rect[1]);
 y1=y0;
 while(y1<(int)g_0066FF74 && (int)g_006769B8[(u32)y1*2+1]<bottom)++y1;
 if(g_0066FF74==0){x0=0;count=0;}
 else {
  u32 lower=0,upper=g_0066FF74,middle=upper>>1;
  u32 threshold=(u32)(int)rect[0]*2u-1u;
  while(lower<upper) {
   if((int)threshold<(int)(g_0066FF78[middle*2+1]<<1)) {upper=middle;middle=(middle+lower)>>1;}
   else {lower=middle+1;middle=(middle+upper+1)>>1;}
  }
  x0=upper;count=g_0066FF74;
 }
 if(y1>y0 && (int)x0<(int)count) {
  do {
   u32 id;
   if((int)g_0066FF78[x0*2+1]>=right)break;
   id=g_0066FF78[x0*2];
   if(g_006BD3D0[id]!=g_006D63EC) {
    QueryUnit *unit;
    g_006BD3D0[id]=g_006D63EC;
    unit=g_0059CB58+id;
    if(g_0059CCA0[id*84]>=y0 && unit->lower<y1)*out++=unit;
    count=g_0066FF74;
   }
   ++x0;
  }while((int)x0<(int)count);
 }
 *out=0;
 g_006BEE64=(u32)((int)((u32)out-(u32)g_006BB938+4u)>>2);
 return start;
}
#pragma code_seg(".root")
QueryUnit **__fastcall compiler_anchor_0042FF80(short *rect) {return sub_0042FF80(rect);}
