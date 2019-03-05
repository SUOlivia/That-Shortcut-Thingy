#pragma once

Result mcuInit();
Result mcuExit();

Result mcuReadRegister(u8 reg, u8* data, u32 size);
Result mcuWriteRegister(u8 reg, u8* data, u32 size);