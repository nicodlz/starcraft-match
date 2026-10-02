#if defined(_MSC_VER)
#define FAST __fastcall
#else
#define FAST __attribute__((fastcall))
#endif
typedef unsigned int U32; typedef int I32; typedef unsigned char U8; typedef short I16; typedef unsigned short U16;
#pragma pack(push,1)
typedef struct Frame { U8 unknown[2]; U8 width,height; U32 data; } Frame;
typedef struct Surface { I16 width,height; U8 *pixels; } Surface;
#pragma pack(pop)
typedef struct Clip { I32 x,y,width,height; } Clip;
extern U8 *data_00597394; extern U32 data_00597390;
extern I16 data_006CEF52,data_006CEF54; extern Surface *data_006CF4A8;
extern void FAST sub_0040ABBE(I32 x,I32 y,const Frame *frame,const Clip *clip,U32 ignored);
#pragma code_seg(".scmatch")
void FAST sub_004BDFA0(I16 input_x,I16 input_y,U32 ignored0,U32 ignored1)
{
 U8 *blob=data_00597394; Frame *frame; Clip clip; I32 x,y,remaining; Surface *surface;
 if(!blob) return;
 frame=(Frame *)(blob+6+(data_00597390%*(U16 *)blob)*8U);
 if(!frame) return;
 clip.x=0; clip.y=0; clip.width=frame->width; clip.height=frame->height;
 x=(I32)data_006CEF52-input_x; y=(I32)data_006CEF54-input_y;
 if(x<0) {clip.width+=x;clip.x=-x;x=0;}
 surface=data_006CF4A8;
 remaining=(I32)surface->width-x;
 if(clip.width>=remaining) clip.width=remaining;
 if(y<0) {clip.height+=y;clip.y=-y;y=0;}
 remaining=(I32)surface->height-y;
 if(clip.height>=remaining) clip.height=remaining;
 sub_0040ABBE(x,y,frame,&clip,0);
}
