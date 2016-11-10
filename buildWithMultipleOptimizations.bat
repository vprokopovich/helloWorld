@echo off
setlocal enabledelayedexpansion

REM set  arrayline[0]=O0
REM set  arrayline[1]=O1
REM set  arrayline[2]=Og
set  arrayline[0]=Od
set  arrayline[1]=Ox

::read it using a FOR /L statement
for /l %%n in (0,1,1) do (
	SET OFLAG=!arrayline[%%n]!
	SET "output=windows!OFLAG!.csv"
	cd solutions
	SET OPTIMIZATION_FLAG=/!OFLAG!
	cmake .\..\src
	cmake --build . --target measures

	..\products\bin\Debug\measures.exe > !output!
	cd ..
)
pause