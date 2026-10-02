#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
extern int sub_00411BB7(void *);
#pragma code_seg(".scmatch")
static NOINLINE int sub_004CE470(void *stream) {
 int ch=sub_00411BB7(stream);
 while(ch!=-1 && ch!=26) ch=sub_00411BB7(stream);
 return ch!=-1;
}
#pragma code_seg(".scctx")
int context_004CE470(void *p) {return sub_004CE470(p);}
