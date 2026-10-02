#if defined(_MSC_VER)
#define FASTCALL __fastcall
#else
#define FASTCALL __attribute__((fastcall))
#endif
struct Event {
    unsigned int code;
    unsigned int value;
    unsigned int unknown_08;
    unsigned short kind;
    unsigned char unknown_0e[6];
};
struct Control;
typedef void (FASTCALL *Callback)(struct Control *, struct Event *);
#pragma pack(push, 1)
struct Control {
    unsigned char unknown_00[0x20];
    unsigned short choice;
    unsigned char unknown_22[8];
    Callback callback;
};
#pragma pack(pop)
typedef char event_size_is_20[sizeof(struct Event) == 20 ? 1 : -1];
typedef char control_size_is_46[sizeof(struct Control) == 46 ? 1 : -1];
void FASTCALL sub_004E88B0(struct Control *control)
{
    struct Event event;
    unsigned short choice = control->choice;
    if (choice == 1)
        event.value = *(volatile unsigned int *)0x006556E4 == 0;
    else if (choice == 2)
        event.value = *(volatile unsigned int *)0x006556E4 == 1;
    else if (choice == 3)
        event.value = *(volatile unsigned int *)0x006556E4 == 2;
    else
        return;
    event.kind = 0xE;
    event.code = 0xB;
    control->callback(control, &event);
}
