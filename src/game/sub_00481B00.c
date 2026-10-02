#if defined(_MSC_VER)
#define SUB00481B00_FASTCALL __fastcall
typedef unsigned int Sub00481B00Address;
#else
#if defined(__i386__)
#define SUB00481B00_FASTCALL __attribute__((fastcall))
#else
#define SUB00481B00_FASTCALL
#endif
typedef __UINTPTR_TYPE__ Sub00481B00Address;
#endif
#pragma pack(push, 1)
typedef struct {
    unsigned int next;
    unsigned char opaque_04[0x1c];
    unsigned short id, kind;
    unsigned char opaque_24[0x0e];
    unsigned int parent;
    unsigned char opaque_36[4];
    short value;
    unsigned char opaque_3c[6];
    unsigned int head;
} Sub00481B00View;
#pragma pack(pop)
typedef char Sub00481B00WordSize[(sizeof(short) == 2) ? 1 : -1];
typedef char Sub00481B00DwordSize[(sizeof(unsigned int) == 4) ? 1 : -1];
typedef char Sub00481B00ViewSize[(sizeof(Sub00481B00View) == 0x46) ? 1 : -1];

/* Inlined source decomposition hypothesis; not a separate matched function. */
static __inline Sub00481B00View *sub_00481B00_find(Sub00481B00View *input,
                                                unsigned short id)
{
    Sub00481B00View *node = input;
    if (input->kind)
        node = (Sub00481B00View *)(Sub00481B00Address)input->parent;
    node = (Sub00481B00View *)(Sub00481B00Address)node->head;
    while (node) {
        if (node->id == id)
            return node;
        node = (Sub00481B00View *)(Sub00481B00Address)node->next;
    }
    return 0;
}

void SUB00481B00_FASTCALL sub_00481B00(Sub00481B00View *input)
{
    Sub00481B00View *node;
    unsigned char mode;
    int value;
    node = sub_00481B00_find(input, 2);
    mode = *(const unsigned char *)0x57f0b4;
    value = node->value;
    if (mode)
        *(int *)0x6cdff0 = value;
    else
        *(int *)0x6cdfd8 = value;
    node = sub_00481B00_find(input, 3);
    value = node->value;
    if (mode)
        *(int *)0x6cdff4 = value;
    else
        *(int *)0x6cdfdc = value;
}
