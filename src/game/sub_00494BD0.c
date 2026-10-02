/* Inputs and result use EAX/ECX and EAX on i386. */
__attribute__((regcall)) unsigned int sub_00494BD0(unsigned int first,
                                                unsigned int second) {
    unsigned int distance = (first - second) & 255u;
    if (distance > 128u)
        distance = 256u - distance;
    return distance;
}
