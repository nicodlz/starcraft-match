void __fastcall sub_00482D30(unsigned char *map, unsigned char *region, unsigned int group)
{
    unsigned short *edges;
    int count;
    *(unsigned short *)(region + 2) = (unsigned short)group;
    if (*(unsigned short *)region == 0x1FFD) {
        unsigned int first = region[6];
        count = (int)region[7] - (int)first;
        edges = *(unsigned short **)(region + 12) + first;
    } else {
        count = region[6];
        edges = *(unsigned short **)(region + 12);
    }
    while (count > 0) {
            unsigned char *next = map + 0x449FC + ((unsigned int)*edges << 6);
            if (*(unsigned short *)(next + 2) == 0)
                sub_00482D30(map, next, group);
            ++edges;
        --count;
    }
}
