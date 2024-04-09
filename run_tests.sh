#!/bin/sh

UM_EXECUTABLE="./um"
TESTS_DIRECTORY="."

# Get a list of all .um files in the current directory
umFiles=$(ls $TESTS_DIRECTORY/*.um)

# Loop over each .um file
for testFile in $umFiles; do
    # Remove the .um extension to get the test name
    testName=$(echo $testFile | sed -E 's/(.*)\.um/\1/')

    # Check if a corresponding .1 file exists
    if [ -f "$TESTS_DIRECTORY/$testName.1" ]; then
        # Run umdump on the .um file and redirect output to a .dump file
        output=$($UM_EXECUTABLE $testFile)

        # Print the test name and output
        echo "Test: $testName"
        echo "Output:"
        echo "$output"
        echo "-------------------------"
    else
        echo "$testName has no output!"
        echo "-------------------------"
        
    fi
done