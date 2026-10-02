typedef unsigned int U32;
typedef unsigned char U8;
#if defined(_MSC_VER)
#define SC __stdcall
#else
#define SC __attribute__((stdcall))
#endif
struct Node {struct Node *next,*previous; U32 unknown8,delay; U8 unknown10[32]; U8 flags;};
extern struct Node *data_0068C100;
extern U8 *data_0068C0FC;
extern void SC sub_0045B850(struct Node *);
#pragma code_seg(".scmatch")
void sub_0045CBD0(void) {
 struct Node *p=data_0068C100;
 if(p) {
  do {
   struct Node *next;
   U32 old;
   if(!p) break;
   old=p->delay;
   next=p->next;
   p->delay=old-1u;
   if(!old) {
    if(p->flags&4u) {
     U8 *owner;
     if(data_0068C100==p) data_0068C100=p->next;
     if(p->previous) p->previous->next=p->next;
     if(p->next) p->next->previous=p->previous;
     owner=data_0068C0FC;
     p->previous=0;
     p->next=*(struct Node **)(owner+0x1450);
     if(*(struct Node **)(owner+0x1450)) (*(struct Node **)(owner+0x1450))->previous=p;
     *(struct Node **)(owner+0x1450)=p;
    } else sub_0045B850(p);
   }
   p=next;
  } while(data_0068C100);
 }
}
#pragma code_seg()
