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
jfino.name=jfino
jfino.vid.0=0x2a03
jfino.pid.0=0x004d
jfino.vid.1=0x2a03
jfino.pid.1=0x804d
jfino.vid.2=0x2a03
jfino.pid.2=0x004e
jfino.vid.3=0x2a03
jfino.pid.3=0x804e
jfino.upload.tool=avrdude
jfino.upload.protocol=stk500v2
jfino.upload.maximum_size=262144
jfino.upload.use_1200bps_touch=true
jfino.upload.wait_for_upload_port=true
jfino.upload.native_usb=true
jfino.upload.speed=57600
jfino.build.mcu=cortex-m0plus
jfino.build.f_cpu=48000000L
jfino.build.usb_product="Arduino M0"
jfino.build.board=SAM_ZERO
jfino.build.core=arduino
jfino.build.extra_flags=-D__SAMD21G18A__ -mthumb {build.usb_flags}
jfino.build.ldscript=linker_scripts/gcc/flash_with_bootloader.ld
jfino.build.variant=jfino
jfino.build.variant_system_lib=
jfino.build.vid=0x2a03
jfino.build.pid=0x804e
jfino.build.preferred_out_format=hex
jfino.bootloader.size=0x4000
jfino.build.emu.mcu=atmega2560
jfino.bootloader.tool=avrdude
jfino.bootloader.low_fuses=0xff

######################################################
#JFINO-ANCHOR (ARDUINO M0 (WITH) BOOTLOADER)
jfino-anchor.name=jfino-anchor
jfino-anchor.vid.0=0x2a03
jfino-anchor.pid.0=0x004d
jfino-anchor.vid.1=0x2a03
jfino-anchor.pid.1=0x804d
jfino-anchor.vid.2=0x2a03
jfino-anchor.pid.2=0x004e
jfino-anchor.vid.3=0x2a03
jfino-anchor.pid.3=0x804e
jfino-anchor.upload.tool=avrdude
jfino-anchor.upload.protocol=stk500v2
jfino-anchor.upload.maximum_size=262144
jfino-anchor.upload.use_1200bps_touch=true
jfino-anchor.upload.wait_for_upload_port=true
jfino-anchor.upload.native_usb=true
jfino-anchor.upload.speed=57600
jfino-anchor.build.mcu=cortex-m0plus
jfino-anchor.build.f_cpu=48000000L
jfino-anchor.build.usb_product="Arduino M0"
jfino-anchor.build.board=SAM_ZERO
jfino-anchor.build.core=arduino
jfino-anchor.build.extra_flags=-D__SAMD21G18A__ -mthumb {build.usb_flags}
jfino-anchor.build.ldscript=linker_scripts/gcc/flash_with_bootloader.ld
jfino-anchor.build.variant=jfino-anchor
jfino-anchor.build.variant_system_lib=
jfino-anchor.build.vid=0x2a03
jfino-anchor.build.pid=0x804e
jfino-anchor.build.preferred_out_format=hex
jfino-anchor.bootloader.size=0x4000
jfino-anchor.build.emu.mcu=atmega2560
jfino-anchor.bootloader.tool=avrdude
jfino-anchor.bootloader.low_fuses=0xff
