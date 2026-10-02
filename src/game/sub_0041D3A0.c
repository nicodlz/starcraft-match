typedef unsigned char U8;
typedef int I32;
typedef unsigned int U32;
typedef struct Rect {I32 left,top,right,bottom;} Rect;
extern U8 *data_006CEFF4;
extern I32 __stdcall sub_00411E4E(U32 surface,U32 flags,U8 **buffer,I32 *stride,U32 unknown);
extern I32 __stdcall sub_004100E2(U8 *destination,U8 *source,I32 width,I32 height,I32 destination_stride,I32 source_stride,U32 reserved,U32 raster_operation);
extern I32 __stdcall sub_00411E48(U32 surface,U8 *buffer,U32 flags,Rect *rectangle);
#pragma code_seg(".scmatch")
static __declspec(noinline) void __stdcall sub_0041D3A0(Rect *rectangle)
{
 U8 *destination;
 I32 stride;
 if(sub_00411E4E(0,0,&destination,&stride,0)) {
  sub_004100E2(destination+rectangle->top*stride+rectangle->left,data_006CEFF4+rectangle->top*640+rectangle->left,rectangle->right-rectangle->left,rectangle->bottom-rectangle->top,stride,640,0,0x00CC0020u);
  sub_00411E48(0,destination,1,rectangle);
 }
}
#pragma code_seg(".scctx")
void context_0041D3A0(Rect *rectangle){sub_0041D3A0(rectangle);}
#pragma code_seg()
