typedef unsigned long U32;
typedef unsigned char U8;
typedef U32 (__stdcall *F0)(void);
typedef U32 (__stdcall *F1)(U32);
typedef U32 (__stdcall *F2)(U32,U32);
typedef U32 (__stdcall *F3)(U32,U32,U32);
typedef U32 (__stdcall *F4)(U32,U32,U32,U32);
typedef U32 (__stdcall *F5)(U32,U32,U32,U32,U32);
typedef U32 (__stdcall *F7)(U32,U32,U32,U32,U32,U32,U32);
typedef U32 (__stdcall *F11)(U32,U32,U32,U32,U32,U32,U32,U32,U32,U32,U32);
#define IAT(a,t) (*(t*)(a))
#if defined(__clang__)
#define _alloca(n) __builtin_alloca(n)
#else
void *__cdecl _alloca(unsigned int);
#pragma intrinsic(_alloca)
#endif
#pragma code_seg(".scmatch")
U32 sub_004E0200(void)
{
 U8 authority[6]={0,0,0,0,0,1};
 U32 process,sid,token,length,result,module;
 U8 acl[512]; U8 *info; F7 dynamic;
 process=IAT(0x4fe23c,F0)();
 sid=0;token=0;length=0;result=0;
 if(!IAT(0x4fe014,F11)((U32)authority,1,0,0,0,0,0,0,0,0,(U32)&sid))goto cleanup;
 if(!IAT(0x4fe024,F3)(process,8,(U32)&token))goto cleanup;
 IAT(0x4fe020,F5)(token,1,0,0,(U32)&length);
 if(length>1024)goto cleanup;
 info=(U8*)_alloca(length);
 if(!IAT(0x4fe020,F5)(token,1,(U32)info,length,(U32)&length))goto cleanup;
 if(!IAT(0x4fe018,F3)((U32)acl,512,2))goto cleanup;
 if(!IAT(0x4fe01c,F4)((U32)acl,2,250,sid))goto cleanup;
 if(!IAT(0x4fe010,F4)((U32)acl,2,0x100701,*(U32*)info))goto cleanup;
 module=IAT(0x4fe234,F1)(0x4ff854);
 if(!module)goto cleanup;
 dynamic=(F7)IAT(0x4fe244,F2)(module,0x4ff844);
 if(!dynamic)goto cleanup;
 if(!dynamic(process,6,0x80000004UL,0,0,(U32)acl,0))result=1;
 cleanup:
 if(token)IAT(0x4fe118,F1)(token);
 if(sid)IAT(0x4fe00c,F1)(sid);
 return result;
}
