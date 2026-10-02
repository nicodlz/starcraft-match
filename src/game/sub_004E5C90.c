typedef unsigned char u8;
typedef unsigned short u16;
struct node { u8 pad[4]; struct node *next; u16 id; };
struct list { u8 pad[28]; struct node *head; };
struct object { u8 pad[12]; struct list *list; u8 pad2[96]; struct object *other; };
static __inline struct node *find_node(struct list *l, unsigned int key)
{
    struct node *n = l->head;
    while (n) {
        if (n->id >= key && n->id <= key) return n;
        n = n->next;
    }
    return (struct node *)0;
}
static __declspec(noinline) unsigned int sub_004E5C90(struct object *p, unsigned int key)
{
    struct node *n = find_node(p->list, key);
    if (!n) {
        n = (struct node *)0;
        if (p->other)
            n = find_node(p->other->list, key);
    }
    return n != (void *)0;
}
unsigned int context_004E5C90(struct object *p, unsigned int key)
{
    return sub_004E5C90(p, key);
}
