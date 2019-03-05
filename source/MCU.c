#include <3ds.h>


Handle mcuHandle = 0;

Result mcuInit()
{
    return srvGetServiceHandle(&mcuHandle, "mcu::HWC");
}

Result mcuExit()
{
    return svcCloseHandle(mcuHandle);
}

Result mcuReadRegister(u8 reg, u8* data, u32 size)
{
    u32* ipc = getThreadCommandBuffer();
    ipc[0] = 0x10082;
    ipc[1] = reg;
    ipc[2] = size;
    ipc[3] = size << 4 | 0xC;
    ipc[4] = data;
    Result ret = svcSendSyncRequest(mcuHandle);
    if(ret < 0) return ret;
    return ipc[1];
}

Result mcuWriteRegister(u8 reg, u8* data, u32 size)
{
    u32* ipc = getThreadCommandBuffer();
    ipc[0] = 0x20082;
    ipc[1] = reg;
    ipc[2] = size;
    ipc[3] = size << 4 | 0xA;
    ipc[4] = data;
    Result ret = svcSendSyncRequest(mcuHandle);
    if(ret < 0) return ret;
    return ipc[1];
}