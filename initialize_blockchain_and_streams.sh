#!bin/bash

if [ $# -eq 0 ]
    then
        echo "ERROR: Please provide the blockchain name to initialize its streams"
        exit 1
fi

cd src
chainName="$1"
./multichain-util create $chainName
./multichaind $chainName -daemon

sleep 3

./multichain-cli $chainName create stream authorityrequests     true

./multichain-cli $chainName create stream authoritynodes        false
./multichain-cli $chainName create stream transactionparams     false
./multichain-cli $chainName create stream records               false
./multichain-cli $chainName create stream annotatedrecords      false
./multichain-cli $chainName create stream badges                false
./multichain-cli $chainName create stream annotatedbadges       false

cd -
