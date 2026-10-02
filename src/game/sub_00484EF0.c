static __declspec(noinline) unsigned int sub_00484EF0(unsigned char value)
{
    unsigned int n=0;
    unsigned char *p=(unsigned char *)0x57f008;
    do {
        unsigned char v=p[-34];
        p-=36;
        if (v==value) {
            v=*p;
            if (v==2 || v==1) ++n;
        }
    } while (p!=(unsigned char *)0x57eee8);
    return n;
}
unsigned int isolated_caller(unsigned char value) {return sub_00484EF0(value);}
