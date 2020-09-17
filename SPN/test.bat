//对拍程序(删掉本行)
@echo off  
:loop  
    rannum.exe > T31.in  
    cipher.exe < T31.in > T31.out
    p3_diffana.exe < T31.out > my.out
    fc my.out T31.in  
if not errorlevel 1 goto loop  
pause  
goto loop