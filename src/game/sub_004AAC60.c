typedef struct Node {unsigned char pad[4];struct Node *next;unsigned char pad2[0x40];unsigned char a,b;unsigned short c;} Node;
static __declspec(noinline) void *sub_004AAC60(unsigned char a,unsigned char b,unsigned short c)
{
 Node *p=*(Node **)0x0051A270;
 if ((long)p<=0) return 0;
 do {
  if (p->a==a && p->b==b && p->c==c) return (unsigned char *)p+0x68;
  p=p->next;
  if ((long)p<=0) return 0;
 } while (p);
 return 0;
}
void *context_004AAC60(unsigned char a,unsigned char b,unsigned short c){return sub_004AAC60(a,b,c);}
