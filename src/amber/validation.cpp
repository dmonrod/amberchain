/* AMB START */

// Amberchain code distributed under the GPLv3 license, see COPYING file.

#include "amber/validation.h"
#include "structs/base58.h"
#include "chain/chain.h"
#include "json/json_spirit.h"
#include "utils/utilstrencodings.h"
#include "core/main.h" // for GetTransaction

using namespace std;
using namespace json_spirit;

void loginvalidblock(const CBlockIndex* pindex, std::string reason)
{
    CPubKey miner  = pindex->kMiner;
    CBitcoinAddress minerAddress(miner.GetID());    

    std::string block_hash = pindex->GetBlockHash().ToString();
    LogPrintf("LogInvalidBlock(): Block hash=%s\n", block_hash);
    LogPrintf("LogInvalidBlock(): Block miner=%s\n", minerAddress.ToString());

    // check if a stream item already exists for this block hash
    // if not, no need to log it again
    Array streamParams;
    streamParams.push_back(STREAM_INVALIDBLOCKS);
    streamParams.push_back(block_hash); 
    Array blockHashItems = liststreamkeyitems(streamParams, false).get_array();
    
    if (blockHashItems.size() == 0) 
    {
        Object data;
        data.push_back(Pair("block-hash", block_hash));
        data.push_back(Pair("miner", minerAddress.ToString()));
        data.push_back(Pair("height", ((pindex->nHeight))));
        data.push_back(Pair("log2-work", (log(pindex->nChainWork.getdouble())/log(2.0))));
        data.push_back(Pair("date", DateTimeStrFormat("%Y-%m-%d %H:%M:%S", pindex->GetBlockTime())));
        data.push_back(Pair("reason", reason));

        const Value& json_data = data;
        const string string_data = write_string(json_data, false);

        string hex_data = HexStr(string_data.begin(), string_data.end());

        Array params;
        params.push_back(STREAM_INVALIDBLOCKS);
        // use block hash as key
        params.push_back(block_hash);
        params.push_back(hex_data);

        // publish will use this node's default address as the "from"
        publish(params, false);
    }

}

vector<CBitcoinAddress> scriptPubKey2Addresses(const CScript& scriptPubKey)
{
    txnouttype type;
    vector<CTxDestination> addresses;
    vector<CBitcoinAddress> addressesOut;
    int nRequired;
    ExtractDestinations(scriptPubKey, type, addresses, nRequired);
    BOOST_FOREACH(const CTxDestination& addr, addresses)
    {
        addressesOut.push_back(CBitcoinAddress(addr));
    }

    return addressesOut;
}

bool IsMinerTx(const CTransaction& tx) 
{
    if (tx.IsCoinBase()) 
    {
        return false;
    }
    BOOST_FOREACH(const CTxIn& txin, tx.vin) 
    {
        CTransaction prevTx;
        uint256 hashBlock = 0;
        if (!GetTransaction(txin.prevout.hash, prevTx, hashBlock, true))
        {
            LogPrintf("IsMinerTx(): Previous transaction could not be retrieved.\n");
            return false;
        }
        CScript scriptPubKey = prevTx.vout[txin.prevout.n].scriptPubKey;
        LogPrintf("IsMinerTx(): scriptPubKey: %s\n", scriptPubKey.ToString());
        BOOST_FOREACH(const CBitcoinAddress address, scriptPubKey2Addresses(scriptPubKey))
        {
            if (haspermission(address.ToString(), "mine")) {
                // if at least one from address is a miner
                return true;
            }
        }
    }

    return false;
}

/* AMB END */

