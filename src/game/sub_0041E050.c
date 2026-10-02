typedef unsigned int U32;
extern void * __cdecl memset(void *,int,U32);
#pragma intrinsic(memset)
extern U32 data_006CEF50[40];
extern U32 data_006CEFF8[300];
extern unsigned short data_006CEFF0;
extern unsigned short data_006CEFF2;
extern U32 data_006CEFF4;
extern U32 data_006D5DF4;
extern const char data_00505E64[];
extern U32 __stdcall sub_0041006A(U32,const char *,U32,U32);
#pragma code_seg(".scmatch")
void sub_0041E050(void) {
 memset(data_006CEF50,0,160);
 memset(data_006CEFF8,0,1200);
 data_006CEFF0=640;
 data_006CEFF2=480;
 data_006CEFF4=0;
 data_006D5DF4=sub_0041006A(2304,data_00505E64,141,0);
}
