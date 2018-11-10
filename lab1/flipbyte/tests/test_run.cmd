@echo off
test.cmd>result.txt

fc result.txt answers.txt > nul
if ERRORLEVEL 1 goto Different
echo Ok
pause
exit
:Different
echo Ne ok
pause

	

