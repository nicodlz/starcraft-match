#if defined(_MSC_VER)
#define SUB004BBCF0_STDCALL __stdcall
#elif defined(__i386__)
#define SUB004BBCF0_STDCALL __attribute__((stdcall))
#else
#define SUB004BBCF0_STDCALL
#endif
typedef unsigned int U32;
typedef int (SUB004BBCF0_STDCALL *Query)(void *, U32 *);
typedef int (SUB004BBCF0_STDCALL *Set)(void *, int);
typedef int (SUB004BBCF0_STDCALL *Play)(void *, U32, U32, U32);
#define OBJ (*(void **)0x006D1268)
void sub_004BBCF0(void)
{
 U32 status;
 void *object;
 int result, level;
 if (!*(void **)0x006D59F4 || !*(int *)0x006CDFE4 || !OBJ) return;
 object=OBJ;
 result=(*(Query **)object)[9](object,&status);
 if (!result && status==1) return;
 level=(int)((U32)*(int *)0x006CDFE4*99U)/100;
 object=OBJ;
 (*(Set **)object)[15](object,(int)(((U32 *)0x005008F0)[level]-*(U32 *)0x006D5A0C));
 object=OBJ;
 (*(Play **)object)[12](object,0,0,0);
}
