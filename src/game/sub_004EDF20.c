typedef unsigned int U32;
typedef void *(__stdcall *Desktop)(void);
typedef int (__stdcall *Folder)(void *,U32,void **);
typedef int (__stdcall *Path)(void *,char *);
typedef U32 (__fastcall *Callback)(const char *,void *,const char *,U32 *);
extern Desktop data_004FE324;
extern Folder data_004FE26C;
extern Path data_004FE268;
extern const char data_00501B74[];
extern U32 __fastcall sub_004EDE60(const char *,void *,const char *,U32 *);
extern U32 __fastcall sub_004CF330(char *,const char *,Callback,U32,U32,const char *,U32 *);
#pragma code_seg(".scmatch")
U32 __stdcall sub_004EDF20(U32 folder,const char *pattern) {
 char path[260]={0};
 void *pidl=0;
 if(data_004FE26C(data_004FE324(),folder,&pidl)!=0) return 0;
 if(!data_004FE268(pidl,path)) return 0;
 folder=0;
 sub_004CF330(path,data_00501B74,sub_004EDE60,0,1,pattern,&folder);
 return folder;
}
