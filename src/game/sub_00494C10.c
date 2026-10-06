#if defined(_MSC_VER)
#define NI __declspec(noinline)
#else
#define NI __attribute__((noinline))
#endif
typedef unsigned int u32;typedef signed int s32;
extern volatile u32 g_00513528[];
#pragma code_seg(".angle")
static NI s32 sub_00494C10(s32 input)
{
 int negative;u32 value,lower,upper,middle;
 if(input<0){negative=1;value=0u-(u32)input;}else{negative=0;value=(u32)input;}upper=64;lower=0;middle=32;
 do {if(value>g_00513528[middle])lower=middle+1;else upper=middle;middle=(upper+lower)>>1;}while(upper!=lower);
 if(negative)middle=0u-middle;
 return (s32)middle;
}
#pragma code_seg(".context")
s32 context_angle(s32 input){return sub_00494C10(input);}
