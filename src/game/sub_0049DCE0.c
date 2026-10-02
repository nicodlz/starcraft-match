/* Observed links only; semantic list names remain community annotations. */
typedef struct Sub0049DCE0Node {
    struct Sub0049DCE0Node *next;
    struct Sub0049DCE0Node *previous;
} Sub0049DCE0Node;

_Static_assert(__builtin_offsetof(Sub0049DCE0Node, previous) == 4,
               "observed i386 DWORD link offset");

__attribute__((regparm(1))) void sub_0049DCE0(Sub0049DCE0Node *node)
{
    Sub0049DCE0Node *anchor =
        *(Sub0049DCE0Node *volatile *)0x006283ECu;
    if (anchor) {
        if (*(Sub0049DCE0Node **)0x00628428u == anchor)
            *(Sub0049DCE0Node *volatile *)0x00628428u = node;
        node->next = anchor;
        node->previous = anchor->previous;
        /* Preserve the second observed DWORD read after the preceding store. */
        Sub0049DCE0Node *previous =
            *(Sub0049DCE0Node *volatile const *)&anchor->previous;
        if (previous)
            previous->next = node;
        anchor->previous = node;
        return;
    }
    *(Sub0049DCE0Node *volatile *)0x00628428u = node;
    *(Sub0049DCE0Node *volatile *)0x006283ECu = node;
}
