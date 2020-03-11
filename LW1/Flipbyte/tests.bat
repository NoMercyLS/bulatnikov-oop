@echo off

SET Program="%~1"

if %Program%=="" (
	echo Please specify path to program Flipbyte.exe
	exit /B 1
)

echo Running Tests...

REM Input file doesnt exists
%Program% "dfsdfsdfsdfsdf.txt" "%TMP%\output.txt" && goto err
echo Test #1 passed!

REM Input line is string
%Program% "tests\inputs\input2.txt" "%TMP%\output.txt" && goto err
echo Test #2 passed!

REM Correct input
%Program% "tests\inputs\input3.txt" "%TMP%\output.txt" || goto err
fc "tests\outputs\output3.txt" "%TMP%\output.txt" > nul || goto err
echo Test #3 passed!

REM Input number bigger than 255
%Program% "tests\inputs\input4.txt" "%TMP%\output.txt" && goto err
echo Test #4 passed!

REM Input number less than 0
%Program% "tests\inputs\input5.txt" "%TMP%\output.txt" && goto err
echo Test #5 passed!

REM Input line is empty
%Program% "tests\inputs\input6.txt" "%TMP%\output.txt" && goto err
echo Test #6 passed!

REM Correct input
%Program% "tests\inputs\input7.txt" "%TMP%\output.txt" || goto err
fc "tests\outputs\output7.txt" "%TMP%\output.txt" > nul || goto err
echo Test #7 passed!

REM Correct input
%Program% "tests\inputs\input8.txt" "%TMP%\output.txt" || goto err
fc "tests\outputs\output8.txt" "%TMP%\output.txt" > nul || goto err
echo Test #8 passed!

REM Tests passed successfully
echo All tests passed successfully
exit /B 0

REM Test failed
:err
echo Test failed!
exit /B 1