typedef unsigned char BYTE;
typedef unsigned int DWORD;
typedef char check_DWORD_width[(sizeof(DWORD) == 4) ? 1 : -1];
extern void __fastcall sub_0040C2BD(DWORD row, DWORD column, DWORD width, DWORD source_offset);
void sub_004BCDC0(void)
{
    volatile BYTE *cache = (volatile BYTE *)0x006CEFF8u;
    DWORD y = *(volatile DWORD *)0x006284A8u;
    DWORD x = *(volatile DWORD *)0x0062848Cu;
    DWORD position = (y * 672u + x) % 301056u;
    int row = 0;
    do {
        int column = 0;
        do {
            if ((int)position >= 301056)
                position -= 301056u;
            if (*cache == 1) {
                int next = column + 1;
                int run = 1;
                DWORD width;
                if (next < 40) {
                    while (next < 40) {
                        if (*cache == 0)
                            break;
                        ++cache;
                        ++run;
                        ++next;

                    }
                }
                width = (DWORD)run * 16u;
                sub_0040C2BD((DWORD)row, (DWORD)column * 16u,
                            width, position);
                position += width - 16u;
                column += run - 1;
                if ((int)position >= 301056)
                    position -= 301056u;
            }
            ++column;
            position += 16u;
            ++cache;
        } while (column < 40);
        position += 10112u;
        if ((int)position >= 301056)
            position -= 301056u;
        row += 16;
    } while (row < 400);
}
