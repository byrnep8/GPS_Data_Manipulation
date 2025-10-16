INCLUDE=-I Include/
BUILD_DIR=build/

haversin:
	echo off
	echo "Compile haversin C file"
	gcc -Wall -g $(INCLUDE) haversin_calc.c -o $(BUILD_DIR)haversin.o -lm
	# chmod a+x haversin.o

clean:
	echo "Cleaning object files"
	rm -rf haversin.o

run:
	$(BUILD_DIR)haversin.o gps_sample_data.csv

