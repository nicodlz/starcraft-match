#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif
struct Node00431F40 { struct Node00431F40 *next; };
unsigned int SC_FASTCALL sub_00431F40(unsigned int index)
{
    struct Node00431F40 *node=*(struct Node00431F40 *volatile *)(0x006AA054u+index*8u);
    unsigned int count=0;
    while(node) {
        node=node->next;
        count++;
    }
    return count;
}
