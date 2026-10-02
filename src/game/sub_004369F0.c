#ifdef _MSC_VER
#define PRIVATE static __declspec(noinline)
#else
#define PRIVATE static __attribute__((noinline))
#endif
PRIVATE unsigned long sub_004369F0(unsigned char *pointer)
{
 unsigned char value=pointer[5];
 if(value==8 || value==9) return 1;
 return 0;
}
unsigned long experiment_caller(unsigned char *pointer) {return sub_004369F0(pointer);}
