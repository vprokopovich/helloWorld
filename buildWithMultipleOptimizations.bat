@echo off
setlocal enabledelayedexpansion

set  arrayline[0]=O0
set  arrayline[1]=O1
set  arrayline[2]=Og
set  arrayline[3]=Od
set  arrayline[4]=Ox

::read it using a FOR /L statement
for /l %%n in (0,1,4) do (
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