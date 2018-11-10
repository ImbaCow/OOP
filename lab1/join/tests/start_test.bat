@echo off
join.exe input_base.txt input_space.txt temp.txt
echo:>result.txt
echo ------->>result.txt
type temp.txt>>result.txt
echo:>>result.txt
join.exe input_base.txt input_base.txt temp.txt
echo  ------->>result.txt
echo:>>result.txt
type temp.txt>>result.txt
echo:>>result.txt
join.exe input_base.txt temp.txt
echo ------->>result.txt
echo:>>result.txt
type temp.txt>>result.txt
echo:>>result.txt
join.exe input_base.txt input_space.txt input_custom.txt temp.txt
echo ------->>result.txt
echo:>>result.txt
type temp.txt>>result.txt
echo:>>result.txt
join.exe input_base.txt input_endl.txt temp.txt
echo ------->>result.txt
echo:>>result.txt
type temp.txt>>result.txt
echo:>>result.txt


fc result.txt answer.txt > nul
if ERRORLEVEL 1 goto Different
echo Ok
pause
exit
:Different
echo Not ok
pause
