typedef unsigned int u32;
typedef struct Entry { void *value; u32 reserved[2]; u32 retain; unsigned char tail[1288]; } Entry;
typedef char Entry_size_check[sizeof(Entry)==1304?1:-1];
extern void __stdcall sub_00410070(void *,const char *,u32,u32);
#pragma code_seg(".scmatch")
void sub_004DC940(void) {
 Entry *p;
 for(p=(Entry *)0x0050E170;(int)p<0x00511E90;++p) {
  void *value=p->value;
  if(value && (!p->retain || !*(u32 *)0x005124D0)) {
   if(*(void **)0x00597394==value) *(void **)0x00597394=0;
   sub_00410070(value,(const char *)0x00502B54,0xcdu,0u);
   p->value=0;
  }
 }
}
