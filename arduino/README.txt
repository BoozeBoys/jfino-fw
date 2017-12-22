Installare in arduino il supporto per le board "ZERO"



Copiare la cartella "jfino-variant" sotto
    "C:\Users\<tuo nome utente>\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.6.17\variants\"
oppure sotto
    "/Users/<tuo nome utente>/Library/Arduino15/packages/arduino/hardware/samd/1.6.17/variants/"
rinominandola solo 
    "jfino"



Aggiungere il seguente testo al file
    "C:\Users\<tuo nome utente>\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.6.17\boards.txt"
oppure al file
    "/Users/<tuo nome utente>/Library/Arduino15/packages/arduino/hardware/samd/1.6.17/boards.txt"

######################################################
#JFINO (for ANCHOR and JFINO)
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
jfino.build.usb_product="jfino"
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
#JFINO-TEST (temp version for using ANCHOR as JFINO board)
jfino-test.name=jfino-test
jfino-test.vid.0=0x2a03
jfino-test.pid.0=0x004d
jfino-test.vid.1=0x2a03
jfino-test.pid.1=0x804d
jfino-test.vid.2=0x2a03
jfino-test.pid.2=0x004e
jfino-test.vid.3=0x2a03
jfino-test.pid.3=0x804e
jfino-test.upload.tool=avrdude
jfino-test.upload.protocol=stk500v2
jfino-test.upload.maximum_size=262144
jfino-test.upload.use_1200bps_touch=true
jfino-test.upload.wait_for_upload_port=true
jfino-test.upload.native_usb=true
jfino-test.upload.speed=57600
jfino-test.build.mcu=cortex-m0plus
jfino-test.build.f_cpu=48000000L
jfino-test.build.usb_product="jfino-test"
jfino-test.build.board=SAM_ZERO
jfino-test.build.core=arduino
jfino-test.build.extra_flags=-D__SAMD21G18A__ -mthumb {build.usb_flags}
jfino-test.build.ldscript=linker_scripts/gcc/flash_with_bootloader.ld
jfino-test.build.variant=jfino-test
jfino-test.build.variant_system_lib=
jfino-test.build.vid=0x2a03
jfino-test.build.pid=0x804e
jfino-test.build.preferred_out_format=hex
jfino-test.bootloader.size=0x4000
jfino-test.build.emu.mcu=atmega2560
jfino-test.bootloader.tool=avrdude
jfino-test.bootloader.low_fuses=0xff
