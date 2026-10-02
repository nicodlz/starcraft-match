#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif

void SC_FASTCALL sub_0049E4E0(unsigned char *unit, unsigned char player)
{
    unsigned char *sprite;
    unsigned char *image;
    unsigned char *next;
    unsigned int type;

    for (;;) {
        sprite = *(unsigned char **)(unit + 0x0C);
        if (sprite[0x0A] != player) {
            sprite[0x0A] = player;
            image = *(unsigned char **)(sprite + 0x1C);
            while (image) {
                *(unsigned short *)(image + 0x0C) |= 1;
                image = *(unsigned char **)(image + 4);
            }
        }
        next = *(unsigned char **)(unit + 0x70);
        if (!next)
            break;
        type = *(const unsigned short *)(next + 0x64);
        if (!(((const unsigned char *)0x00664080u)[type * 4] & 0x10))
            break;
        unit = next;
    }
}
