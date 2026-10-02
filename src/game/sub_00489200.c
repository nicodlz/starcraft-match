#if defined(_MSC_VER)
#define FAST __fastcall
#define NOINLINE __declspec(noinline)
#else
#define FAST __attribute__((fastcall))
#define NOINLINE __attribute__((noinline))
#endif
 typedef int (FAST *Condition)(unsigned char *);
static NOINLINE int sub_00489200(unsigned char *object) {
 int i=0; unsigned char *p=object+23;
 do {
  if (!(p[2]&2)) { unsigned char type=p[0]; if (!type) return 1; if (!((Condition *)0x00515A98)[type](p-15)) return 0; }
  ++i;p+=20;
 } while(i<16);
 return 1;
}
int context(unsigned char *object) { return sub_00489200(object); }
