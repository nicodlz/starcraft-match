void sub_004DC5B0(void)
{
    switch (*(const unsigned int *)0x59688cu) {
    case 0x41544c4bu:
    case 0x4950584eu:
    case 0x49505858u:
    case 0x5544504eu:
        *(unsigned int *)0x6d11bcu = 10;
        break;
    case 0x424e4554u:
        *(unsigned int *)0x6d11bcu = 4;
        break;
    case 0x4d444d58u:
    case 0x4d4f444du:
        *(unsigned int *)0x6d11bcu = 20;
        break;
    case 0x5343424cu:
        *(unsigned int *)0x6d11bcu = 21;
        break;
    default:
        *(unsigned int *)0x6d11bcu = 0;
        break;
    }
}
