haversin:
	echo off
	echo "Compile haversin C file"
	gcc -Wall haversin_calc.c -o haversin.o -lm
	# chmod a+x haversin.o

clean:
	echo "Cleaning object files"
	rm -rf haversin.o

run:
	./haversin.o 'activity_19091828100.tcx.xlsx - Sheet1.csv'

