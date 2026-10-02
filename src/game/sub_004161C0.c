typedef unsigned short (__stdcall *Lang)(void);
typedef int (__stdcall *Lead)(unsigned char);
extern unsigned int __cdecl strlen(const char *);
static __declspec(noinline) unsigned int sub_004161C0(const char *text, unsigned int position)
{
    unsigned int index;
    if ((*(Lang *)0x004fe14c)()!=0x0412) return 0;
    index=0;
    if (strlen(text)) {
        do {
            if ((*(Lead *)0x004fe1c4)((unsigned char)text[index])) {
                if (position==index) return 1;
                ++index;
                if (position==index) return 2;
            } else if (position==index) return 0;
            ++index;
        } while (index<strlen(text));
    }
    return 0;
}
unsigned int context_004161C0(const char *text, unsigned int position)
{ return sub_004161C0(text,position); }
