typedef unsigned int U32;
typedef unsigned char U8;
#if defined(_MSC_VER)
#define SC __stdcall
#else
#define SC __attribute__((stdcall))
#endif
extern U32 data_0066FBFC,data_0057F090,data_006D5A30,data_00596888;
extern U8 data_0066FBFA;
extern void SC sub_0044FD30(U32);
extern void sub_00471270(void);
#pragma code_seg(".scmatch")
void sub_004719D0(void) {
 U32 count=data_0066FBFC;
 if(!count) return;
 --count;
 data_0066FBFC=count;
 if(count==data_0057F090*2u+4u) {
  sub_0044FD30(data_006D5A30);
  count=data_0066FBFC;
  data_0066FBFA=6;
 }
 if(count==data_0057F090+2u) {
  if(data_00596888) {
   data_0066FBFA=7;
   sub_00471270();
   count=data_0066FBFC;
  } else data_0066FBFA=8;
 }
 if(!count) data_0066FBFA=9;
}
#pragma code_seg()
