/* Independent C, compiler context selects observed query register. */
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
extern int sub_0040CB2B(const char *,const char *);
struct Node {struct Node *previous,*next;unsigned unknown;char text[1];};
#pragma code_seg(".scmatch")
static NOINLINE struct Node *sub_004617C0(const char *query) {
 int head=*(int*)0x0051a324;
 struct Node *node=(struct Node*)(head>0?head:0);
 while((int)node>0) {
  if(!sub_0040CB2B(query,node->text))return node;
  if(!node)node=(struct Node*)0x0051a320;
  node=node->next;
 }
 return 0;
}
#pragma code_seg(".scctx")
struct Node *context_004617C0(const char *query) {return sub_004617C0(query);}
