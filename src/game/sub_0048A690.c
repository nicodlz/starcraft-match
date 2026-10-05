/* Both pool declarations bind to the same reviewed data address. */
typedef unsigned int u32;
typedef struct Node {struct Node *next,*previous;unsigned char rest[104];} Node;
typedef char sc_node112_size[(sizeof(Node)==112)?1:-1];
extern Node g_0064B2E8[100],g_0064B2E8_loop[100];
extern Node *g_0064EED8,*g_0064EEDC,*g_0064DEC4,*g_0064DEAC;
extern u32 g_0064DEBC;
void *__cdecl memset(void*,int,u32);
#pragma intrinsic(memset)
#pragma code_seg(".pool")
void sub_0048A690(void) {
 Node *base,*entry;u32 count;
 memset(g_0064B2E8,0,11200);
 base=g_0064B2E8;
 g_0064DEBC=0;g_0064EEDC=base;g_0064EED8=base;g_0064DEAC=0;g_0064DEC4=0;
 base=g_0064B2E8_loop;entry=base+1;count=99;
 do {
  if(g_0064EEDC==base)g_0064EEDC=entry;
  entry->next=base;entry->previous=base->previous;
  if(base->previous)base->previous->next=entry;
  base->previous=entry;++entry;
 }while(--count);
}
