/* Independent C reconstruction; context helpers are hypothetical and uncounted. */
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define FASTCALL __fastcall
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define FASTCALL __attribute__((fastcall))
#define STDCALL __attribute__((stdcall))
#endif
static NOINLINE int STDCALL sub_0047A670(int numerator,int denominator,int *output,int scale) {
 int percent, value, remainder;
 if (denominator) percent=(int)((unsigned)numerator*100u)/denominator; else percent=100;
 value=(int)((unsigned)percent*(unsigned)scale)/100;
 if(value<3)value=3;
 remainder=value%3;
 if(remainder) {
  if(remainder>1)value+=3-remainder;
  else value-=remainder;
 }
 *output=value;
 return percent;
}
int context(int a,int b,int *p,int s) { return sub_0047A670(a,b,p,s); }
