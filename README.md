# High-Speed CMSIS-DAP for STLINK-V3MINI ARM Debugger 

Keywords: USB2.0 High-Speed CMSIS-DAP STLINK-V3 STM32F723IEK6 SWO VCP CDC DAPLink ST-LINK ARM-Debugger

ST company created a great mini-size ARM debugger STLINK-V3MINI for STM32 MCU, cost you ~US$10 only. Re-Use the high-performance PCBA hardware, you can do more interesting projects or hobbies. 

![alt text](https://github.com/RadioOperator/CMSIS-DAP_for_STLINK-V3MINI/blob/master/STLINK-V3MINI/Pics/STLINK-V3MINI_p3.jpg)

A new very good/low-cost Starter Kit ...... what we got:

 - MCU: STM32F723IEK6, Arm® Cortex®-M7 32b MCU+FPU, 462DMIPS.
 - Core speed: 216MHz
 - ROM: 512KB
 - RAM: 256+16+4KB, new features.
 - USB 2.0 High-Speed internal PHY.
 - GPIO, up to 30s connected out in STLINK-V3MINI PCBA.
 - UART, SPI, I2C, CAN, ADC, more...
 - some GPIO with ESD protection.
 - On-board LEDs.
 
 
## My code:
   -  /STLINKv3DAPv1_HID+VCP ------- native HID+VCP mode, CMSIS-DAP v1, VCP(CDC) added.
   -  /STLINKv3DAPv2_WinUSB --------- native WinUSB mode, CMSIS-DAP v2, SWO_STREAM mode enabled.
   -  /STLINKv3DAPv2_WinUSB+VCP --- WinUSB+VCP, SWO_STREAM mode cannot enable.
   -  /STLINKv3DAP_v1+v2 -------------- v1+v2, no VCP, SWO_STREAM mode cannot enable.

All support SWD and JTAG mode.  SWO_STREAM mode is important or not? please tell me.

v1+v2, HID and WinUSB mode coexisted, suggest disable one in Device Manager force to another.

The STDC14 connector pin definations:

   -  Pin-1,  NC.
   -  Pin-2,  NC.
   - *Pin-3,  3.3V out, re-wire to STLINK 3.3V LDO output, limited less than 50mA.
   -  Pin-4,  JTMS / SWDIO.
   -  Pin-5,  GND.
   -  Pin-6,  JTCK / SWCLK (same as Pin-9) .
   -  Pin-7,  GND.
   -  Pin-8,  JTDO / SWO.
   -  Pin-9,  JTCK / SWCLK (same as Pin-6) .
   -  Pin-10, JTDI.
   - *Pin-11, NC (GND Detect on STLINK, to target GND for ST-LINK).
   - *Pin-12, nRESET (T-NRST on STLINK), to JTAG/SWD nRESET pin, or board /RESET.
   -  Pin-13, VCP Tx.
   -  Pin-14, VCP Rx.
  
 *---Not same as STLINK-V3MINI original.

## Compile Environment:
   - Keil: v5.28a.
   - STM32F7xx_DFP 2.12.0.
   - Keil: ARM CMSIS 5.6.0.
   - Keil: MDK-Middleware 7.9.0.
   - Keil: ARM Compiler 6 (AC6 + MicroLIB, Optimization[-Ofast]).
   

Include Path:
  - C:\Keil\ARM\PACK\ARM\CMSIS\5.6.0\CMSIS\Include            - maybe not same as yours.
  - C:\Keil\ARM\PACK\ARM\CMSIS\5.6.0\CMSIS\Driver\Include     - maybe not same as yours.
  - .\CMSIS-DAP
  - .\RTE\USB
  - .\USER


## Some issues:
1. not well-tested, need your report.
2. Stack uasge check and optimize, not performed.
3. ......


## Further improvements:
1. General USB-DFU bootloader, support drag&drop easy update any user App, need your help.
2. Try using other USB library to see what happened.
3. Develop SPI/I2C/CAN bus, Logic analyzer/emulator functions, we have a large flash room.
4. ......


## Important Warning:
---------------------
The original STLINK-V3 device Firmware has been protected by ST company. Any normal methods, to try to read-back/program the original Flash ROM, will trigger a mass ERASE of the internal flash. This could cause your STLINK-V3 function total lost permanently, and cannot recover the factory firmware by yourself. When you decided to program the STLINK-V3MINI flash, it means the device will be no longer STLINK-V3MINI any more.
