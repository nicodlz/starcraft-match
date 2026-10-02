typedef unsigned int U32;
#if defined(_MSC_VER)
#define ST __stdcall
#define NI __declspec(noinline)
#else
#define ST __attribute__((stdcall))
#define NI __attribute__((noinline))
#endif
extern const char *ST sub_00410088(const char *,U32);
extern U32 ST sub_00410094(const char *,const char *,U32);
#pragma code_seg(".scmatch")
static NI U32 sub_004DBD20(U32 *index,const char *path,U32 count)
{
 const char *component;
 while(*index<65U) {
  component=((const char **)0x0059C080)[*index];
  component=sub_00410088(component,92U);
  if(component && sub_00410094(component+1,path,count)==0) return 1;
  ++*index;
 }
 return 0;
}
#pragma code_seg(".scctx")
U32 context(U32 *index,const char *path,U32 count) { return sub_004DBD20(index,path,count); }
