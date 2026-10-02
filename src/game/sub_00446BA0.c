__attribute__((regparm(1))) void sub_00446BA0(unsigned int index) {
    volatile unsigned char *p=(volatile unsigned char *)(0x690000u+index*0x4e8u);
    unsigned char count=p[0xfb];
    p[0x101]&=0xf7;
    if(count) p[0xfb]=count-1;
}
