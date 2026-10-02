typedef unsigned long u32;
#if defined(_MSC_VER)
#define STDCALL __stdcall
#else
#define STDCALL __attribute__((stdcall))
#endif
typedef u32 (STDCALL *Fn0)(void);
typedef u32 (STDCALL *Fn1)(u32);
typedef u32 (STDCALL *Fn2)(u32,u32);
typedef struct MetricsView { int height; unsigned char remaining[52]; } MetricsView;
typedef char MetricsSizeCheck[(sizeof(MetricsView) == 56) ? 1 : -1];
typedef int (STDCALL *FnMetrics)(u32,MetricsView *);
#define VIEW(address,type) (*(type *)(address))
int STDCALL sub_0044A000(u32 object)
{
    MetricsView metrics;
    u32 screen = VIEW(0x004FE304,Fn1)(VIEW(0x004FE324,Fn0)());
    u32 dc = VIEW(0x004FE054,Fn1)(screen);
    int height;
    object = VIEW(0x004FE04C,Fn2)(dc,object);
    height = -1;
    if (VIEW(0x004FE05C,FnMetrics)(dc,&metrics))
        height = metrics.height;
    VIEW(0x004FE04C,Fn2)(dc,object);
    VIEW(0x004FE038,Fn1)(dc);
    VIEW(0x004FE30C,Fn2)(VIEW(0x004FE324,Fn0)(),screen);
    return height;
}
