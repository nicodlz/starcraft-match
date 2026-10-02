typedef struct LinkView0049DCA0 {
    struct LinkView0049DCA0 *link0;
    struct LinkView0049DCA0 * volatile link4;
} LinkView0049DCA0;

#if defined(_MSC_VER) && !defined(__clang__)
#define PRIVATE_LEAF __declspec(noinline)
#else
#define PRIVATE_LEAF __attribute__((noinline,regparm(1)))
#endif

static PRIVATE_LEAF LinkView0049DCA0 *sub_0049DCA0(LinkView0049DCA0 *node) {
    LinkView0049DCA0 *head=*(LinkView0049DCA0 **)0x00628430u;
    if(head!=0) {
        LinkView0049DCA0 *previous;
        if(*(LinkView0049DCA0 **)0x0059CC9Cu==head)
            *(LinkView0049DCA0 **)0x0059CC9Cu=node;
        node->link0=head;
        node->link4=head->link4;
        previous=head->link4;
        if(previous!=0)
            previous->link0=node;
        head->link4=node;
    } else {
        *(LinkView0049DCA0 **)0x0059CC9Cu=node;
        *(LinkView0049DCA0 **)0x00628430u=node;
    }
    return node;
}

/* Independent compiler context; this helper is not a reconstructed function. */
LinkView0049DCA0 *compiler_context_0049DCA0(LinkView0049DCA0 *node) {
    return sub_0049DCA0(node);
}
