#!/bin/bash

if ! hash python; then
    echo "Python 2.7 is required to run tests"
    exit 1
fi

py=$(python -V 2>&1 | sed 's/.* \([0-9]\).\([0-9]\).*/\1\2/')
if [[ "$py" -lt "27" ||  "$py" -gt "30" ]]
then
    echo "This script requires Python 2.7.X installed"
    exit 1
fi

# Install Pytest
sudo pip install -U pytest

# Check version
pytest --version 
 
# Run tests
sudo pytest python/libmath_test.py 

exit 0