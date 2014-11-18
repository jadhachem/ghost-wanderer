#!/bin/bash

failed=""
if [ -a unit_test.log ]
then
	rm unit_test.log
fi

echo "Starting unit tests"
echo "-------------------"
for unit_test in $@
do
	{ ./${unit_test} &>> unit_test.log; } &>> /dev/null
	if [ $? -eq 0 ]
	then
		echo "Unit test ${unit_test} successful!"
	else
		echo "*** Unit test ${unit_test} FAILED!"
		failed="${failed}${unit_test} "
	fi
done

echo "-------------------"
if [ -z "${failed}" ]
then
	echo "All unit tests were successful"
else
	echo "Unit tests that failed: ${failed}"
	echo "Errors logged in unit_test.log"
fi

