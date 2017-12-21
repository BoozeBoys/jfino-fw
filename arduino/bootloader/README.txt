Collegare la board al programmatore J-Link come riportato sotto:

SEGGER JLINK BASE                       JFINO JLINK
    -----                              -------------
 1 | X X | 2                                 ---    |
 3 | X X | 4                              1 |X X| 2 | 
 5 | X X | 6            1<--->2           3 |X X| 4 | 
 7 | X X | 8            4<--->6           5 |X X| 6 |
 9|  X X | 10           7<--->5              ---    |
11|  X X | 12           9<--->3                     |
13 | X X | 14          15<--->1                     |
15 | X X | 16                                       |
17 | X X | 18                                       |
19 | X X | 20                                       |
    -----                                           |



Tramite il menu "Tools->Device Programming" di Atmel Studio eseguire l'upload del file bootloader.hex



!!! ATTENZIONE !!!
Qualora fosse necessario riprogrammare un micro già flashato 
in precedenza è necessario sbloccare il bootloader.
Per farlo, impostare il parametro FUSE USER_WORD_0.NVMCTRL_BOOTPROT a 0x07
