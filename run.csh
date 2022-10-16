#!/bin/bash

echo "====> making eventgen"

make eventgen

echo "====> make check; executing eventgen; saving events in eventdata & eventdata.root"

./eventgen > eventdata
