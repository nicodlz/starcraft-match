typedef unsigned char u8;
typedef void (__fastcall *Callback)(u8 *, void *);
static __declspec(noinline) void sub_00417F00(u8 *node, void *argument, Callback callback)
{
    while (node) {
        u8 *next;
        if (*(unsigned short *)(node+0x22)==0)
            next=*(u8 **)(node+0x42);
        else next=*(u8 **)node;
        callback(node,argument);
        node=next;
    }
}
void context_00417F00(u8 *node, void *argument, Callback callback)
{ sub_00417F00(node,argument,callback); }
