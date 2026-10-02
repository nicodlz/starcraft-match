typedef int (__stdcall *Method)(void *, void *, unsigned int);
static __declspec(noinline) unsigned int sub_004BB600(int *error, void *window)
{
    void *object=*(void **)0x006d59f4;
    *error=(*(Method **)object)[6](object,window,2);
    if (*error) {
        object=*(void **)0x006d59f4;
        *error=(*(Method **)object)[6](object,window,1);
        if (*error) {
            error[2]=0x00502cb0;
            return 0;
        }
    }
    return 1;
}
unsigned int context_004BB600(int *error, void *window)
{ return sub_004BB600(error,window); }
