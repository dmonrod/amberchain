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

./amberchain-cli $chainName create stream authorityrequests         true
./amberchain-cli $chainName create stream invalidblocks             true
./amberchain-cli $chainName create stream customcategories          true
./amberchain-cli $chainName create stream updatecustomcategories    true

./amberchain-cli $chainName create stream authoritynodes            false
./amberchain-cli $chainName create stream transactionparams         false
./amberchain-cli $chainName create stream records                   false
./amberchain-cli $chainName create stream annotatedrecords          false
./amberchain-cli $chainName create stream badges                    false
./amberchain-cli $chainName create stream issuedbadges              false
./amberchain-cli $chainName create stream issuebadgerequests        false
./amberchain-cli $chainName create stream badgeissuers              false
./amberchain-cli $chainName create stream annotatedbadges           false
./amberchain-cli $chainName create stream categories                false
./amberchain-cli $chainName create stream updatecategories          false
./amberchain-cli $chainName create stream recordtypes               false

cd -
