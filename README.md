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


### Linux Build Notes (on Ubuntu 14.04 x64)
=================

Install dependencies
--------------------

    sudo apt-get update
    sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils
    sudo apt-get install libboost-all-dev
    sudo apt-get install git
    sudo apt-get install software-properties-common
    sudo add-apt-repository ppa:bitcoin/bitcoin
    sudo apt-get update
    sudo apt-get install libdb4.8-dev libdb4.8++-dev

Compile Amberchain for Ubuntu (64-bit)
-----------------------------

    ./autogen.sh
    ./configure
    make

Notes
-----

* This will build `amberchaind`, `amberchain-cli` and `amberchain-util` in the `src` directory.

* The release is built with GCC after which `strip amberchaind` strings the debug symbols, which reduces the executable size by about 90%.