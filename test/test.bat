@echo off

set SUDOKUEXE=C:\CODE\Sudoku-generator\test\sudoku\Debug\sudoku.exe
set SOURCES=C:\CODE\Sudoku-generator\test\sudoku


echo run good test

OpenCppCoverage --export_type=binary:cov/c-50.cov --sources %SOURCES% -- %SUDOKUEXE% -c 50

OpenCppCoverage --export_type=binary:cov/n-50.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50

OpenCppCoverage --export_type=binary:cov/n-50-m-1.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -m 1
OpenCppCoverage --export_type=binary:cov/n-50-m-2.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -m 2
OpenCppCoverage --export_type=binary:cov/n-50-m-3.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -m 3

OpenCppCoverage --export_type=binary:cov/n-50-r-25-50.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -r 25~50

OpenCppCoverage --export_type=binary:cov/n-50-m-3-r-25-50.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -m 3 -r 25~50

OpenCppCoverage --export_type=binary:cov/n-50-m-1-u.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -m 3 -u

OpenCppCoverage --export_type=binary:cov/sr.cov --sources %SOURCES% -- %SUDOKUEXE% -s C:\CODE\Sudoku-generator\test\board_1.txt
OpenCppCoverage --export_type=binary:cov/sd.cov --sources %SOURCES% -- %SUDOKUEXE% -s .\board_1.txt

OpenCppCoverage --export_type=binary:cov/all.cov --sources %SOURCES% -- %SUDOKUEXE% -c 50 -n 50 -m 3 -r 25~50 -s .\board_1.txt -u

echo run bad test

OpenCppCoverage --export_type=binary:cov/e-b.cov --sources %SOURCES% -- %SUDOKUEXE% -t a

OpenCppCoverage --export_type=binary:cov/c-b1.cov --sources %SOURCES% -- %SUDOKUEXE% -c
OpenCppCoverage --export_type=binary:cov/c-b2.cov --sources %SOURCES% -- %SUDOKUEXE% -c 50a
OpenCppCoverage --export_type=binary:cov/c-b3.cov --sources %SOURCES% -- %SUDOKUEXE% -c 1000001

OpenCppCoverage --export_type=binary:cov/n-b1.cov --sources %SOURCES% -- %SUDOKUEXE% -n
OpenCppCoverage --export_type=binary:cov/n-b2.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50a
OpenCppCoverage --export_type=binary:cov/n-b3.cov --sources %SOURCES% -- %SUDOKUEXE% -n 1000001

OpenCppCoverage --export_type=binary:cov/m-b1.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -m
OpenCppCoverage --export_type=binary:cov/m-b2.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -m a
OpenCppCoverage --export_type=binary:cov/m-b3.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -m 4
OpenCppCoverage --export_type=binary:cov/m-b4.cov --sources %SOURCES% -- %SUDOKUEXE% -m 1

OpenCppCoverage --export_type=binary:cov/r-b1.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -r
OpenCppCoverage --export_type=binary:cov/r-b2.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -r 10~50
OpenCppCoverage --export_type=binary:cov/r-b3.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -r 25~20
OpenCppCoverage --export_type=binary:cov/r-b4.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -r ~
OpenCppCoverage --export_type=binary:cov/r-b5.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -r 25
OpenCppCoverage --export_type=binary:cov/r-b6.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -r 25~30~40
OpenCppCoverage --export_type=binary:cov/r-b7.cov --sources %SOURCES% -- %SUDOKUEXE% -n 50 -r 25a~30
OpenCppCoverage --export_type=binary:cov/r-b8.cov --sources %SOURCES% -- %SUDOKUEXE% -r 25~50

OpenCppCoverage --export_type=binary:cov/u-b.cov --sources %SOURCES% -- %SUDOKUEXE% -u

OpenCppCoverage --export_type=binary:cov/s-b0.cov --sources %SOURCES% -- %SUDOKUEXE% -s .\board_0.txt
OpenCppCoverage --export_type=binary:cov/s-b1.cov --sources %SOURCES% -- %SUDOKUEXE% -s .\bad_board_1.txt
OpenCppCoverage --export_type=binary:cov/s-b2.cov --sources %SOURCES% -- %SUDOKUEXE% -s .\bad_board_2.txt
OpenCppCoverage --export_type=binary:cov/s-b3.cov --sources %SOURCES% -- %SUDOKUEXE% -s .\bad_board_3.txt
OpenCppCoverage --export_type=binary:cov/s-b4.cov --sources %SOURCES% -- %SUDOKUEXE% -s .\bad_board_4.txt
OpenCppCoverage --export_type=binary:cov/s-b5.cov --sources %SOURCES% -- %SUDOKUEXE% -s .\bad_board_5.txt
OpenCppCoverage --export_type=binary:cov/s-b6.cov --sources %SOURCES% -- %SUDOKUEXE% -s .\bad_board_6.txt