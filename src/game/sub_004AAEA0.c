/* Independent C reconstruction; absolute addresses describe the pinned i386 image. */
#if defined(_MSC_VER) && !defined(__clang__)
typedef unsigned sc_size;
typedef int sc_signed_address;
#define SC_STDCALL __stdcall
#else
typedef __SIZE_TYPE__ sc_size;
typedef __INTPTR_TYPE__ sc_signed_address;
#if defined(__i386__)
#define SC_STDCALL __attribute__((stdcall))
#else
#define SC_STDCALL
#endif
#endif
#if defined(_MSC_VER) && !defined(__clang__)
void *memcpy(void *, const void *, sc_size);
int memcmp(const void *, const void *, sc_size);
#pragma intrinsic(memcpy, memcmp)
#endif
void SC_STDCALL sub_004AAEA0(unsigned char *event){
 unsigned char *node;unsigned char a,b;unsigned short c;unsigned char *selected; unsigned char *data;
 data=*(unsigned char**)(event+8);
 node=*(unsigned char**)0x51A270u;
 if((sc_signed_address)node>0){
  a=*(unsigned char*)0x596820u;b=*(unsigned char*)0x596821u;c=*(unsigned short*)0x596822u;
  do{if(node[0x48]==a && node[0x49]==b && *(unsigned short*)(node+0x4a)==c){selected=node+0x48;goto found;}
   node=*(unsigned char**)(node+4);
  if((sc_signed_address)node<=0) break;
  }while(node);
 }
 selected=0; found:;
#if defined(_MSC_VER) && !defined(__clang__)
 if(*(unsigned*)(event+12)==32 && selected && memcmp(selected,data,32)==0){memcpy((void*)0x596865u,selected,32);return;}
#else
 if(*(unsigned*)(event+12)==32 && selected){
  unsigned i;
  const volatile unsigned *source=(const volatile unsigned *)selected;
  const volatile unsigned *payload=(const volatile unsigned *)data;
  volatile unsigned *destination=(volatile unsigned *)0x596865u;
  for(i=0;i<8;i++){
   if(source[i]!=payload[i])break;
  }
  if(i==8){
   for(i=0;i<8;i++)destination[i]=source[i];
   return;
  }
 }
#endif
 *(unsigned char*)0x596865u=0xff;
}
