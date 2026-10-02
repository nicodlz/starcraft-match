#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
#define SC_FASTCALL __fastcall
#else
#define SC_NOINLINE __attribute__((noinline))
#define SC_FASTCALL __attribute__((fastcall))
#endif
/* Recorded MSVC whole-TU optimization supplies AX/CL to this static leaf. */
static SC_NOINLINE void sub_0042CE70(unsigned short type, unsigned char player) {
    unsigned int type_offset = (unsigned int)type * 2u;
    unsigned int player_offset = (unsigned int)player * 4u;
    int mineral = (int)*(volatile unsigned short *)(0x00663888u + type_offset) * 3 / 4;
    unsigned int minerals = *(volatile unsigned int *)(0x0057F0F0u + player_offset) + (unsigned int)mineral;
    int gas = (int)*(volatile unsigned short *)(0x0065FD00u + type_offset);
    *(volatile unsigned int *)(0x0057F0F0u + player_offset) = minerals;
    gas = gas * 3 / 4;
    *(volatile unsigned int *)(0x0057F120u + player_offset) += (unsigned int)gas;
}
/* Compiler source-shape scaffold only; not a reconstructed game caller. */
void SC_FASTCALL independent_probe_0042CE70(unsigned short type, unsigned char player) {
    sub_0042CE70(type, player);
}
