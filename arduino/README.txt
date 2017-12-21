Installare in arduino il supporto per le board "ZERO".



Copiare la cartella "jfino-variant" 
sotto "C:\Users\<tuo nome utente>\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.6.17\variants\"
sotto "/Users/<tuo nome utente>/Library/Arduino15/packages/arduino/hardware/samd/1.6.17/variants/"
rinominandola solo "jfino".



Aggiungere il seguente testo al file
"C:\Users\<tuo nome utente>\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.6.17\boards.txt"
"/Users/<tuo nome utente>/Library/Arduino15/packages/arduino/hardware/samd/1.6.17/boards.txt"

######################################################
#JFINO (ARDUINO M0 (WITH) BOOTLOADER)
mzero_bl.name=jfino
mzero_bl.vid.0=0x2a03
mzero_bl.pid.0=0x004d
mzero_bl.vid.1=0x2a03
mzero_bl.pid.1=0x804d
mzero_bl.vid.2=0x2a03
mzero_bl.pid.2=0x004e
mzero_bl.vid.3=0x2a03
mzero_bl.pid.3=0x804e
mzero_bl.upload.tool=avrdude
mzero_bl.upload.protocol=stk500v2
mzero_bl.upload.maximum_size=262144
mzero_bl.upload.use_1200bps_touch=true
mzero_bl.upload.wait_for_upload_port=true
mzero_bl.upload.native_usb=true
mzero_bl.upload.speed=57600
mzero_bl.build.mcu=cortex-m0plus
mzero_bl.build.f_cpu=48000000L
mzero_bl.build.usb_product="Arduino M0"
mzero_bl.build.board=SAM_ZERO
mzero_bl.build.core=arduino
mzero_bl.build.extra_flags=-D__SAMD21G18A__ -mthumb {build.usb_flags}
mzero_bl.build.ldscript=linker_scripts/gcc/flash_with_bootloader.ld
mzero_bl.build.variant=jfino
mzero_bl.build.variant_system_lib=
mzero_bl.build.vid=0x2a03
mzero_bl.build.pid=0x804e
mzero_bl.build.preferred_out_format=hex
mzero_bl.bootloader.size=0x4000
mzero_bl.build.emu.mcu=atmega2560
mzero_bl.bootloader.tool=avrdude
mzero_bl.bootloader.low_fuses=0xff

######################################################
#JFINO-ANCHOR (ARDUINO M0 (WITH) BOOTLOADER)
mzero_bl.name=jfino-anchor
mzero_bl.vid.0=0x2a03
mzero_bl.pid.0=0x004d
mzero_bl.vid.1=0x2a03
mzero_bl.pid.1=0x804d
mzero_bl.vid.2=0x2a03
mzero_bl.pid.2=0x004e
mzero_bl.vid.3=0x2a03
mzero_bl.pid.3=0x804e
mzero_bl.upload.tool=avrdude
mzero_bl.upload.protocol=stk500v2
mzero_bl.upload.maximum_size=262144
mzero_bl.upload.use_1200bps_touch=true
mzero_bl.upload.wait_for_upload_port=true
mzero_bl.upload.native_usb=true
mzero_bl.upload.speed=57600
mzero_bl.build.mcu=cortex-m0plus
mzero_bl.build.f_cpu=48000000L
mzero_bl.build.usb_product="Arduino M0"
mzero_bl.build.board=SAM_ZERO
mzero_bl.build.core=arduino
mzero_bl.build.extra_flags=-D__SAMD21G18A__ -mthumb {build.usb_flags}
mzero_bl.build.ldscript=linker_scripts/gcc/flash_with_bootloader.ld
mzero_bl.build.variant=jfino
mzero_bl.build.variant_system_lib=
mzero_bl.build.vid=0x2a03
mzero_bl.build.pid=0x804e
mzero_bl.build.preferred_out_format=hex
mzero_bl.bootloader.size=0x4000
mzero_bl.build.emu.mcu=atmega2560
mzero_bl.bootloader.tool=avrdude
mzero_bl.bootloader.low_fuses=0xff
