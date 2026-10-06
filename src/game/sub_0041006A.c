/* Reviewed import slot DATA, not an implementation of the imported service. */
typedef unsigned int u32;
typedef void *(__stdcall *Import_004FE568)(u32 size,const char *file,u32 line,u32 flags);
#pragma code_seg(".tail")
__declspec(noinline) void *__stdcall sub_0041006A(u32 size,const char *file,u32 line,u32 flags)
{
    return (*(Import_004FE568 const *)0x004FE568u)(size,file,line,flags);
}
