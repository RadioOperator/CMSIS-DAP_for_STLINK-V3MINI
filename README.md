# High-Speed CMSIS-DAP for STLINK-V3MINI ARM Debugger 

Keywords: USB2.0 High-Speed CMSIS-DAP STLINK-V3 STM32F723IEK6 SWO VCP CDC DAPLink ST-LINK ARM-Debugger

ST company created a great mini-size ARM debugger STLINK-V3MINI for STM32 MCU, cost you ~US$10 only. Re-Use the high-performance PCBA hardware, you can do more interesting projects or hobbies. 

## Important Notice:
 This repo is an old project for CMSIS-DAP!!! If you are a new comer here, please visit my Yet_Another_Bootloader (YAB) repo first on  
 https://github.com/RadioOperator/Yet_Another_Bootloader.  
 Please try to install the YAB first. YAB (STLINKv3_YAB project) could co-exist with STLINK-V3 Factory Bootloader, and install one or two of pre-built CMSIS-DAP code to test the DAP function, no need to destroy the factory bootloader.
 
 Beacuse the factory bootloader still in the device, it's very easy to recover STLINK-V3 functions using STSW-LINK007 update tools.
 (please DONOT use the new verion STSW-LINK007 v2.36.26 or later, the new version will locked the STM32F723 IC's SWD port).  
 

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
   - Keil: MDK-Middleware 7.10.0.
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
1. General USB-DFU bootloader, support drag&drop easy update any user App.  
>>  2020-07-24 update: MSC Bootloader function is Done!  
>>  visit: https://github.com/RadioOperator/Yet_Another_Bootloader  

2. Try using other USB library to see what happened.
3. Develop SPI/I2C/CAN bus, Logic analyzer/emulator functions, we have a large flash room.
4. ......


## New Release Notes:
  - 2019-12-22, improved SWD clock, max 18MHz (Keil - 10MHz). USB VID changed to ST VID=0x0483 for all.
  The USB PID as following:
    - STLINKv3DAPv1_HID+VCP -------- PID 0x572C
    - STLINKv3DAPv2_WinUSB+VCP --- PID 0x572D
    - STLINKv3DAPv2_WinUSB ---------- PID 0x572E
    - STLINKv3DAP_v1+v2 -------------- PID 0x572F
    - My STM32F103C8T6 project ------ PID 0x572A ([STM32F103C8T6_CMSIS-DAP_SWO])
    
    [STM32F103C8T6_CMSIS-DAP_SWO]: https://github.com/RadioOperator/STM32F103C8T6_CMSIS-DAP_SWO


### Declarations:  
  
>  The project is for experiments only. Use any parts and info on your own risks.  

