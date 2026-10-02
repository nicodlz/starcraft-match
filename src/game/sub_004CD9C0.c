typedef short i16;
void __fastcall sub_004CD9C0(i16 *p)
{
    if (*(const i16 *)0x00596904 == 4) {
        p[2] = (i16)((640 - p[4]) / 2);
        p[3] = (i16)((480 - p[5]) / 2);
    }
}
