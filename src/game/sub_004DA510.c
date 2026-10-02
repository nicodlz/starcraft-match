typedef unsigned int U32;
extern void *data_006CE0F4[4];
extern U32 data_006D11D4;
extern const char data_00505D44[];
extern void __stdcall sub_00410070(void *,const char *,U32,U32);
#pragma code_seg(".scmatch")
void sub_004DA510(void) {
 void **slot=data_006CE0F4;
 do {
  void *object=*slot;
  if(object) {
   *(U32 *)object=0;
   sub_00410070(object,data_00505D44,124,0);
   *slot=0;
  }
  slot++;
 } while((int)slot<(int)(data_006CE0F4+4));
 data_006D11D4=0;
}
