#!bin/bash

cd src
chainName="$1"
./multichain-util create $chainName
./multichaind $chainName -daemon
(
printf "create stream authorityrequests true\n"
printf "create stream authorithynodes false\n"
printf "create stream transactionparams false\n"
printf "create stream records false\n"
printf "create stream annotatedrecords false\n"
printf "exit\n"
) | ./multichain-cli $chainName
cd -