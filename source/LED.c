#include <3ds.h>
#include <string.h>

Handle ptmsysmHandle = 0;

Result ptmsysmInit()
{
    return srvGetServiceHandle(&ptmsysmHandle, "ptm:sysm");
}

Result ptmsysmExit()
{
    return svcCloseHandle(ptmsysmHandle);
}

typedef struct
{
    u32 ani;
    u8 r[32];
    u8 g[32];
    u8 b[32];
} RGBLedPattern;

Result ptmsysmSetInfoLedPattern(RGBLedPattern pattern)
{
    u32* ipc = getThreadCommandBuffer();
    ipc[0] = 0x8010640;
    memcpy(&ipc[1], &pattern, 0x64);
    Result ret = svcSendSyncRequest(ptmsysmHandle);
    if(ret < 0) return ret;
    return ipc[1];
}

void fixcolor(u8 r, u8 g, u8 b)
{
    RGBLedPattern pat;
    memset(&pat.r, r, 32);
    memset(&pat.g, g, 32);
    memset(&pat.b, b, 32);
    pat.ani = 0xFF0000;
    if(ptmsysmInit() < 0) return;
    ptmsysmSetInfoLedPattern(pat);
    ptmsysmExit();
}

void stfuled()
{
    RGBLedPattern pat;
    memset(&pat, 0, sizeof(pat));
    pat.ani = 0xFF0000;
    if(ptmsysmInit() < 0) return;
    ptmsysmSetInfoLedPattern(pat);
    ptmsysmExit();
}