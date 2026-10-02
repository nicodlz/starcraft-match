typedef unsigned char U8;
typedef unsigned int U32;
typedef char U32Width[(sizeof(U32)==4)?1:-1];
extern char data_00599A90[];
/* External pinned thunk; resolved only by standard linker code binding. */
extern void __stdcall sub_0041008E(char *destination,const char *source,U32 capacity);
#pragma code_seg(".scmatch")
static __declspec(noinline) void sub_004B65D0(U8 *object)
{
    U8 *node;
    if (*(unsigned short *)(object+0x22)) object=*(U8 **)(object+0x32);
    node=*(U8 **)(object+0x42);
    if (node) do {
        if (*(unsigned short *)(node+0x20)==4) goto found;
        node=*(U8 **)node;
    } while(node);
    node=0;
found:
    /* No null guard: missing matching node reaches a read at address 0x14. */
    sub_0041008E(data_00599A90,*(const char **)((U32)node+0x14U),255);
}

#pragma code_seg(".scctx")
void context_004B65D0(U8 *object) { sub_004B65D0(object); }
