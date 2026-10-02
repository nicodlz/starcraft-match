typedef unsigned int U32;
extern const char data_005056A4[];
extern int __stdcall sub_00410070(void *allocation,const char *file,U32 line,U32 flags);
#pragma code_seg(".scmatch")
__declspec(noinline) static void sub_0042BBD0(U32 *object) {
 sub_00410070((void *)object[0],data_005056A4,0x97,0);
 sub_00410070((void *)object[1],data_005056A4,0x98,0);
 sub_00410070((void *)object[2],data_005056A4,0x99,0);
 sub_00410070((void *)object[3],data_005056A4,0x9A,0);
}
#pragma code_seg(".scctx")
__declspec(noinline) void context_0042BBD0(U32 *object) { sub_0042BBD0(object); }
#pragma code_seg()
