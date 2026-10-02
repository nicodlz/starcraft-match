#pragma code_seg(".scmatch")
#if defined(_MSC_VER)
#define FASTCALL __fastcall
#else
#define FASTCALL __attribute__((fastcall))
#endif
typedef unsigned char u8;
typedef unsigned int u32;
struct Node { u32 unknown; struct Node *next; u32 key; };
/* First ECX argument is explicitly ignored by the observed helper; EDX is string. */
extern u32 FASTCALL sub_004B7CB0(void *ignored_table, const char *string);
u32 *FASTCALL sub_004B7DA0(u8 *object)
{
    const char **table;
    u32 key;
    struct Node *node;
    u8 index;
    if (object[0x46] == 0)
        return 0;
    index = object[0x48];
    if (index == 0xFF)
        return 0;
    table = *(const char ***)(object + 0x3A);
    key = sub_004B7CB0((void *)table, table[index]);
    node = *(struct Node **)0x0051A1F8;
    if ((int)(u32)node > 0) {
        do {
            if (node->key == key)
                return &node->key;
            node = node->next;
        } while ((int)(u32)node > 0 && node != 0);
    }
    return 0;
}
