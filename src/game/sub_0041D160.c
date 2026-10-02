#ifdef _MSC_VER
#define PRIVATE static __declspec(noinline)
#define STDCALL __stdcall
#else
#define PRIVATE static __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned short U16;
typedef unsigned long U32;
typedef struct Output {U16 first; U16 second; unsigned char *pointer;} Output;
PRIVATE void STDCALL sub_0041D160(unsigned char index, unsigned char *table, Output *output, U16 *a,U16 *b,U16 *c,U16 *d)
{
 unsigned char *entry; U16 value; U32 offset;
 if((U16)index>=*(U16 *)table) index=0;
 entry=table+6+8*(U32)index;
 *a=entry[0]; *b=entry[1];
 *c=*(U16 *)(table+2); *d=*(U16 *)(table+4);
 output->second=entry[3];
 value=entry[2]; offset=*(U32 *)(entry+4);
 if(offset&0x80000000UL) {offset&=0x7fffffffUL;value+=256;}
 output->first=value; output->pointer=table+offset;
}
void experiment_caller(unsigned char index,unsigned char *table,Output *output,U16 *a,U16 *b,U16 *c,U16 *d)
{sub_0041D160(index,table,output,a,b,c,d);}
