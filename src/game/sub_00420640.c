typedef struct {
    unsigned int kind;
    unsigned int ignored04;
    unsigned int ignored08;
    unsigned int mask;
    unsigned int setting;
    unsigned int *destination;
} Option00420640;
/* Layout and type dispatch observed in the pinned PE. */
typedef char Option00420640_size[(sizeof(Option00420640) == 24) ? 1 : -1];
void sub_00420640(void) {
    Option00420640 *option = (Option00420640 *)0x00519F68u;
    unsigned int remaining = 16;
    do {
        switch (option->kind) {
        case 0:
            *(unsigned char *)option->destination = 0;
            break;
        case 1:
            *option->destination = option->setting;
            break;
        case 2:
            if (option->setting)
                *option->destination |= option->mask;
            else
                *option->destination &= ~option->mask;
            break;
        }
        ++option;
    } while (--remaining);
}
