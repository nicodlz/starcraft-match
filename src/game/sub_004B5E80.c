struct node { int unused; struct node *next; int payload; };
struct node *__fastcall sub_004B5E80(void *target)
{
    struct node *node = *(struct node **)0x0051a240;
    if ((int)node > 0) {
        do {
            if (&node->payload == target)
                return node;
            node = node->next;
            if ((int)node <= 0)
                break;
        } while (node);
    }
    return 0;
}
