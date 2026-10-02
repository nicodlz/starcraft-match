typedef unsigned int U32;
#define SC __stdcall
#define CELL(a) (*(U32 *)(a))
typedef void (SC *LockFn)(void *);
typedef U32 (SC *SeekFn)(U32,U32,void *,U32);
typedef U32 (SC *WriteFn)(U32,const void *,U32,U32 *,void *);
typedef U32 (SC *CloseFn)(U32);
extern LockFn p_enter,p_leave;
extern SeekFn p_seek;
extern WriteFn p_write;
extern CloseFn p_close;
extern U32 sub_0041ECB0(void);
#pragma code_seg(".scmatch")
void sub_0041EE50(U32 close_flag)
{
 U32 written;
 p_enter((void *)0x006D62B8);
 if(CELL(0x006D5DEC)) {
  if(CELL(0x0051B290)==0xFFFFFFFFU) {
   U32 handle=sub_0041ECB0();
   CELL(0x0051B290)=handle;
   if(handle==0xFFFFFFFFU) {CELL(0x006D5DEC)=0;return;}
   p_seek(handle,0,0,2);
  }
  p_write(CELL(0x0051B290),(void *)CELL(0x006D5DE8),CELL(0x006D5DEC),&written,0);
  CELL(0x006D5DEC)=0;
 }
 if(close_flag && CELL(0x0051B290)!=0xFFFFFFFFU) {p_close(CELL(0x0051B290));CELL(0x0051B290)=0xFFFFFFFFU;}
 p_leave((void *)0x006D62B8);
}
