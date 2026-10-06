typedef unsigned short u16;
typedef short s16;
typedef struct Image {struct Image *prev,*next; unsigned char pad[4];u16 flags;} Image;
typedef struct Sprite {struct Sprite *prev,*next;unsigned char pad[12];s16 x,y;unsigned char pad2[4];Image *images;} Sprite;
#ifdef _MSC_VER
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
#define HEAD ((Sprite **)0x629688)
#define TAIL ((Sprite **)0x629288)
#define HEIGHT (*(u16 *)0x57F1D6)

#pragma code_seg(".fn")
static NOINLINE void sub_00497A10(Sprite *s,s16 x,s16 y) {
 int oldrow,newrow; Sprite *head; Image *image;
 if(s->x==x && s->y==y) return;
 {int row=s->y/32;
 if(row<0)oldrow=0;else {int height=HEIGHT; oldrow=height-1; if(row<height)oldrow=row;}}
 newrow=y/32;
 s->x=x;s->y=y;
 if(newrow<0)newrow=0;else {int height=HEIGHT; if(newrow>=height)newrow=height-1;}
 if(oldrow!=newrow){
  if(HEAD[oldrow]==s)HEAD[oldrow]=s->next;
  if(TAIL[oldrow]==s)TAIL[oldrow]=s->prev;
  if(s->prev)s->prev->next=s->next;
  if(s->next)s->next->prev=s->prev;
  s->prev=0;s->next=0;
  head=HEAD[newrow];
  if(head){
   if(TAIL[newrow]==head)TAIL[newrow]=s;
   s->prev=head;s->next=head->next;
   if(head->next)head->next->prev=s;
   head->next=s;
  }else{TAIL[newrow]=s;HEAD[newrow]=s;}
 }
 image=s->images;
 while(image){image->flags|=1;image=image->next;}
}

#pragma code_seg(".anchor")
void context_00497A10(Sprite *s,s16 x,s16 y) {sub_00497A10(s,x,y);}
