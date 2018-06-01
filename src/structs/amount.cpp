// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Original code was distributed under the MIT software license.
// Copyright (c) 2014-2017 Coin Sciences Ltd
// MultiChain code distributed under the GPLv3 license, see COPYING file.

#include "structs/amount.h"

#include "utils/tinyformat.h"

#include "amber/streamutils.h"

CFeeRate::CFeeRate(const CAmount& nFeePaid, size_t nSize)
{
    if (nSize > 0)
        nSatoshisPerK = nFeePaid*1000/nSize;
    else
        nSatoshisPerK = 0;
}

CAmount CFeeRate::GetFee(size_t nSize) const
{
    /* AMB START */

    unsigned int minRelayTxFee = StreamUtils::GetMinimumRelayTxFee();

    /* AMB END */
    CAmount nFee = minRelayTxFee*nSize / 1000;

    if (nFee == 0 && minRelayTxFee > 0)
        nFee = minRelayTxFee;

    return nFee;
}

std::string CFeeRate::ToString() const
{
/* MCHN START */    
    if(COIN == 0)
    {
        return strprintf("%d.%08d BTC/kB", nSatoshisPerK, nSatoshisPerK);        
    }
/* MCHN END */    
    return strprintf("%d.%08d BTC/kB", nSatoshisPerK / COIN, nSatoshisPerK % COIN);
}
