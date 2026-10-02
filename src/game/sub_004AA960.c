typedef unsigned char u8;
void * __fastcall sub_004AA960(void *unused, u8 key)
{
    u8 *p = *(u8 **)0x0051A270;
    void *result = 0;
    if ((int)p > 0) {
        do {
            if (key == p[0x48]) { result = p + 0x68; break; }
            p = *(u8 **)(p + 4);
            if ((int)p <= 0) break;
        } while (p);
    }
    return result;
}
