@echo off

SET Program="%~1"

if %Program%=="" (
	echo Please specify path to program Replace.exe
	exit /B 1
)

echo Running Tests...

REM Empty input
echo Empty input
%Program% "tests\inputs\input11.txt" "tests\inputs\input12.txt" && goto err
fc "output.txt" "tests\outputs\output1.txt" > nul || goto err
echo Test #1 passed!
echo --------------------

REM Input file doesn't exists
echo Input file doesn't exists
%Program% "NoFile.txt" "NoFile2.txt" && goto err
fc "output.txt" "tests\outputs\output2.txt" > nul || goto err
echo Test #2 passed!
echo --------------------

REM Incorrect number of arguments
echo Incorrect number of arguments
%Program% "tests\inputs\input12.txt" "tests\inputs\input11" 12 12 12 12 && goto err
fc "output.txt" "tests\outputs\output3.txt" > nul || goto err
echo Test #3 passed!
echo --------------------

REM Incorrect number of arguments #2
echo Incorrect number of arguments #2
%Program% && goto err
fc "output.txt" "tests\outputs\output3.txt" > nul || goto err
echo Test #4 passed!
echo --------------------

REM Correct input
echo Correct input
%Program% "tests\inputs\input51.txt" "tests\inputs\input52.txt" || goto err
fc "output.txt" "tests\outputs\output5.txt" > nul || goto err
echo Test #5 passed!
echo --------------------

REM Correct input #2
echo Correct input #2
%Program% "tests\inputs\input6.txt" "tests\inputs\input6.txt" || goto err
fc "output.txt" "tests\outputs\output6.txt" > nul || goto err
echo Test #6 passed!
echo --------------------

REM Tests passed successfully
echo All tests passed successfully!
exit /B 0

REM Test failed
:err
echo Test failed!!!
exit /B 1