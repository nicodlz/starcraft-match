typedef unsigned char u8;
struct node { u8 pad[4]; struct node *next; };
struct context { u8 pad[14]; u8 flags; u8 pad2[13]; struct node *head; };
struct animation_argument { unsigned int value; };
/* Aggregate parameter forces one DWORD stack slot while EDX is unused. */
extern void __fastcall sub_004D8470(struct node *p, struct animation_argument animation);
#if defined(_MSC_VER) && !defined(__clang__)
#pragma code_seg(".scmatch")
#endif
void __fastcall sub_00499D00(struct context *p, unsigned int unused_edx, unsigned int animation, unsigned int force)
{
    struct node *n = p->head;
    struct animation_argument a;
    a.value = animation;
    (void)unused_edx;
    while (n) {
        if (force || !(p->flags & 0x80))
            sub_004D8470(n, a);
        n = n->next;
    }
}
