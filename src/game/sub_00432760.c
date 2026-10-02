#if defined(_MSC_VER)
#define SUB00432760_FASTCALL __fastcall
typedef unsigned int Sub00432760Address;
#else
#if defined(__i386__)
#define SUB00432760_FASTCALL __attribute__((fastcall))
#else
#define SUB00432760_FASTCALL
#endif
typedef __UINTPTR_TYPE__ Sub00432760Address;
#endif

typedef struct {
    unsigned char opaque[0x64];
    unsigned short type;
} Sub00432760Unit;
typedef struct {
    unsigned int next;
    unsigned char opaque[0x18];
    unsigned char enabled, changed;
    unsigned char opaque_1e[0x0e];
    unsigned int slots[4];
} Sub00432760Node;
typedef char Sub00432760WordSize[(sizeof(unsigned short) == 2) ? 1 : -1];
typedef char Sub00432760DwordSize[(sizeof(unsigned int) == 4) ? 1 : -1];
typedef char Sub00432760NodeSize[(sizeof(Sub00432760Node) == 0x3c) ? 1 : -1];

void SUB00432760_FASTCALL sub_00432760(const Sub00432760Unit *unit)
{
    unsigned int offset;
    if (!(((const unsigned int *)0x664080)[unit->type] & 0x2000u))
        return;
    for (offset = 0; offset < 0x40; offset += 8) {
        Sub00432760Node *node = (Sub00432760Node *)(Sub00432760Address)
            *(const unsigned int *)(Sub00432760Address)(offset + 0x6aa054u);
        if (node) do {
            if (node->slots[0] == (unsigned int)(Sub00432760Address)unit)
                node->slots[0] = 0;
            if (node->slots[1] == (unsigned int)(Sub00432760Address)unit)
                node->slots[1] = 0;
            if (node->slots[2] == (unsigned int)(Sub00432760Address)unit)
                node->slots[2] = 0;
            if (node->slots[3] == (unsigned int)(Sub00432760Address)unit)
                node->slots[3] = 0;
            if (node->enabled)
                node->changed = 1;
            node = (Sub00432760Node *)(Sub00432760Address)node->next;
        } while (node);
    }
}
