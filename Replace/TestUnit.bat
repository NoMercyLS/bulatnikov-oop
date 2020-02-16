@echo off

SET Program="%~1"

if %Program%=="" (
	echo Please specify path to program Replace.exe
	exit /B 1
)

echo Running Tests...

REM Empty input
%Program% "tests\inputs\input1.txt" "output.txt" 12 12 || goto err
fc "tests\outputs\output1.txt" "output.txt" > nul || goto err
echo Test #1 passed!

REM Input file doesn't exists
%Program% "NoFile.txt" "output.txt" 12 12 && goto err
echo Test #2 passed!

REM Incorrect number of arguments
%Program% "tests\inputs\input3.txt" "output.txt" 12 12 12 12 && goto err
echo Test #3 passed!

REM Incorrect number of arguments #2
%Program% && goto err
echo Test #4 passed!

REM Replacement on itself
%Program% "tests\inputs\input5.txt" "output.txt" 0 0 || goto err
fc "tests\outputs\output5.txt" "output.txt" > nul || goto err
echo Test #5 passed!

REM Replacement on double substring
%Program% "tests\inputs\input6.txt" "output.txt" 12 1212 || goto err
fc "tests\outputs\output6.txt" "output.txt" > nul || goto err
echo Test #6 passed!

REM Test from task
%Program% "tests\inputs\input7.txt" "output.txt" 1231234 g || goto err
fc "tests\outputs\output7.txt" "output.txt" > nul || goto err
echo Test #7 passed!

REM Wrong arguments
%Program% 1 1 1 1 && goto err
echo Test #8 passed!

REM Sought string is empty 
%Program% "tests\inputs\input9.txt" "tests\outputs\output9.txt" "" "gegegege" && goto err
echo Test #9 passed!

REM Tests passed successfully
echo All tests passed successfully
exit /B 0

REM Test failed
:err
echo Test failed!
exit /B 1
