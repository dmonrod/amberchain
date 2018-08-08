#!/bin/bash

if [ $# -eq 0 ]
    then
        echo "ERROR: Please provide the blockchain name to initialize its streams"
        exit 1
fi

cd src
chainName="$1"
./amberchain-util create $chainName
./amberchaind $chainName -daemon

sleep 3

cd ..

./create_streams.sh $chainName

cd -
