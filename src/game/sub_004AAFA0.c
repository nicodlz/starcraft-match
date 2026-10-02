typedef struct Node {unsigned char pad[4];struct Node *next;unsigned char pad2[0x40];unsigned char a,b;unsigned short c;} Node;
static __forceinline unsigned char *lookup_004AAFA0(unsigned char a,unsigned char b,unsigned short c)
{
 Node *p=*(Node **)0x0051A270;
 if ((long)p<=0) return 0;
 do {
  if(p->a==a && p->b==b && p->c==c) return (unsigned char *)p+0x48;
  p=p->next;
  if ((long)p<=0) return 0;
 } while(p);
 return 0;
}
static __declspec(noinline) int sub_004AAFA0(unsigned char a,unsigned char b,unsigned short c)
{
 unsigned char *header=lookup_004AAFA0(a,b,c);
 if(!header) return 0;
 return header[8]==1;
}
int context_004AAFA0(unsigned char a,unsigned char b,unsigned short c){return sub_004AAFA0(a,b,c);}
