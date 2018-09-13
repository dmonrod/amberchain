AmberChain
==========

AmberChain is the blockchain implementation for the [AmberTime](https://ambertime.org/) platform. AmberTime blockchain is focused on providing a platform for education + travel applications.

AmberChain is based on the popular open source [MultiChain](http://www.multichain.com/), customized with a host of innovative features including new API calls, support for an ecommerce marketplace, automated escrow management, and additional transaction fee parameters.

    Copyright (c) 2018 Apsaras Group Ltd
    License: GNU General Public License version 3, see COPYING

    Portions copyright (c) 2014-2017 Coin Sciences Ltd
    Portions copyright (c) 2009-2016 The Bitcoin Core developers
    Portions copyright many others - see individual files

## Setup instructions

Refer to the original multichain instructions [here](multichain-README.md)

-----------------------------

### Linux Build Notes (on Ubuntu 14.04 x64)


1. Clone a the Amberchain repository on your local directory
    ```python
    # if git is not installed
    sudo apt-get install git
    git clone https://github.com/ambertime/amberchain.git
    ```

2.  Install the required tools and libraries
    ```python
    sudo apt-get update
    sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils
    sudo apt-get install libboost-all-dev
    sudo apt-get install software-properties-common
    sudo add-apt-repository ppa:bitcoin/bitcoin
    sudo apt-get update
    sudo apt-get install libdb4.8-dev libdb4.8++-dev
    ```

3. Build the Chain 
    
    Compile Amberchain for Ubuntu (64-bit)
    ```python
    # amberchain/src >
    make
    # this will take a few minutes  to build the chain
    ```
* This will build `amberchaind`, `amberchain-cli` and `amberchain-util` in the `src` directory.

* The release is built with GCC after which `strip amberchaind` strings the debug symbols, which reduces the executable size by about 90%.
    
    ```python
    # Initialize and create the Amber Chain run in amberchain folder
   
    ./initialize_blockchain_and_streams.sh <chain name>

    # ie. ./initialize_blockchain_and_streams.sh amber-testchain
    ```

4. Start a Chain 
    ```python
    # amberchain/src >
    # -daemon flag runs the chain in the background
    ./amberchaind <chain name> -daemon 
    # ie: ./amberchaind amber-testchain -daemon
    ```
    **When creating an application that connects to the API of a new chain* 
    *   *copy credentials from multichain.conf*
    *   *set port*
    *   *set chain name*

5. Run the Chain CLI
    ```python
    # amberchain/src >
    ./amberchain-cli <chain name>
    # ie: ./amberchain-cli amber-testchain
    ```
    * You can run the _help_ command in the CLI to see a list of APIs
    * help <API name> shows a detailed description of th API and parameters
    ```python
    # amber-testchain > 
    help
    help listaddresses 
    ```

6. Stop the Chain

    * You can stop the chain by running the stop command from outside the CLI
    ```python
    # amberchain/src >
    ./amberchain-cli <chain name> stop
    # ie. ./amberchain-cli amber-testchain stop
    ```
    * Inside the CLI 
    ```python
    # amber-testchain > 
    stop
    bye
    ```

7. Delete the Chain
    ```python
    rm -rf ~/.multichain/<chain name>
    # ie. rm -rf ~/.multichain/amber-testchain
    ```


