extern unsigned char *sub_0049A850(void);
void sub_004BFCD0(void)
{
 unsigned char *unit,*linked;
 unsigned short type;
 *(unsigned char *)0x006284B6=0;
 unit=sub_0049A850();
 while(unit) {
  type=*(unsigned short *)(unit+0x64);
  if(type==1 || type==16 || type==100 || type==99 || type==104) {
   linked=*(unsigned char **)(unit+0x80);
   if(linked && *(unsigned short *)(linked+0x64)==14) {
    *(unsigned int *)(unit+0x80)=0;
    *(unsigned int *)(linked+0x80)=0;
   }
  }
  unit=sub_0049A850();
 }
}
