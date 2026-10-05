#include "sub_0048FC70.c"
extern u8 g_0057F0B4, g_00596875;
extern u32 g_00512684;
extern u8 g_0058D634[];
#pragma code_seg(".select")
void sub_0048FDB0(void) {
 u8 *flags;
 u32 index;
 g_0057F1DA=0;
 if(g_0057F0B4 && g_00596875) {
  u8 *group;
  flags=g_0058D634+g_00512684*12;
  group=(u8*)g_0057EEE4+6;
  do {
   if(*flags)sub_0048FC70(*group);
   group+=36;
   ++flags;
  } while((int)(u32)group < (int)(u32)((u8*)g_0057EEE4+294));
  return;
 }
 index=g_00512684*12;
 if(g_0058D634[index])g_0057F1DA=(u16)(1u<<g_0057EEE4[0].id);
#define SELECT(n) if(g_0058D634[index+(n)])g_0057F1DA|=(u16)(1u<<g_0057EEE4[n].id);
 SELECT(1) SELECT(2) SELECT(3) SELECT(4) SELECT(5) SELECT(6) SELECT(7)
#undef SELECT
}
