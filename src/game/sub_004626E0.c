#if defined(_MSC_VER) && !defined(__clang__)
#define NI __declspec(noinline)
#else
#define NI __attribute__((noinline))
#endif
typedef struct Node Node;
struct Node { Node *next,*previous; unsigned int field08,field0c; };
typedef struct { unsigned char a[0x7d00]; Node *head; } Owner;
#if (defined(_MSC_VER) && !defined(__clang__)) || defined(__i386__)
#if defined(_MSC_VER) && !defined(__clang__)
#define OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
#else
#define OFFSET(type,member) __builtin_offsetof(type,member)
#endif
typedef char pointer_width[(sizeof(Node *) == 4) ? 1 : -1];
typedef char node_next_offset[(OFFSET(Node,next) == 0) ? 1 : -1];
typedef char node_previous_offset[(OFFSET(Node,previous) == 4) ? 1 : -1];
typedef char node_field0c_offset[(OFFSET(Node,field0c) == 0xc) ? 1 : -1];
typedef char owner_head_offset[(OFFSET(Owner,head) == 0x7d00) ? 1 : -1];
#endif
static NI void sub_004626E0(unsigned int index) {
 Node *node=((Node *volatile *)0x68510cu)[index*2u];
 if(!node) return;
 do {
  Node *next;
  if(!node) break;
  next=node->next;
  if(!node->field0c) {
   Owner *owner;
   if(((Node *volatile *)0x68510cu)[index*2u]==node) ((Node *volatile *)0x68510cu)[index*2u]=node->next;
   if(node->previous) node->previous->next=node->next;
   if(node->next) node->next->previous=node->previous;
   owner=((Owner *const *)0x685108u)[index*2u];
   node->previous=0;
   node->next=owner->head;
   if(owner->head) owner->head->previous=node;
   owner->head=node;
  }
  node=next;
 } while(((Node *volatile *)0x68510cu)[index*2u]);
}
/* Independent C compiler context, neither reconstructed nor counted. */
void source_context_004626E0(unsigned int index) { sub_004626E0(index); }
