#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif
typedef unsigned int u32;
typedef unsigned short u16;
struct Event004195E0 { u32 kind, zero, untouched; u16 type, x, y, trailing; };
typedef void (SC_FASTCALL *Callback004195E0)(void *, struct Event004195E0 *);
void sub_004195E0(void)
{
    void **slot = (void **)0x006D5E40;
    struct Event004195E0 event;
    do {
        void *object = *slot;
        if (object) {
            u16 y = *(u16 *)0x006CDDC8;
            u16 x = *(u16 *)0x006CDDC4;
            event.y = y;
            event.type = 0xE;
            event.kind = 6;
            event.zero = 0;
            event.x = x;
            (*(Callback004195E0 *)((unsigned char *)object + 0x2A))(object, &event);
            *slot = 0;
        }
        ++slot;
    } while ((int)slot < 0x006D5E8C);
}
