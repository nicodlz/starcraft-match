#if defined(_MSC_VER)
#define SC_00493100_LEAF __declspec(noinline)
#else
#define SC_00493100_LEAF __attribute__((noinline, regparm(1)))
#endif

typedef struct Node00493100 {
    unsigned char ignored[248];
    struct Node00493100 *next;
    struct Node00493100 *previous;
} Node00493100;
SC_00493100_LEAF static void sub_00493100(Node00493100 *node) {
    Node00493100 *next = node->next;
    Node00493100 *previous;
    if (next) next->previous = node->previous;
    previous = node->previous;
    if (previous) previous->next = node->next;
    if (*(Node00493100 **)0x0063FF54u == node) {
        node->next = 0;
        *(Node00493100 **)0x0063FF54u = node->previous;
    } else {
        node->next = 0;
    }
    node->previous = 0;
}
/* Compilation anchor: independently authored source-shape experiment, not a game match. */
void compiler_anchor_00493100(Node00493100 *node) { sub_00493100(node); }
