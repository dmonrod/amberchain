// Amberchain code distributed under the GPLv3 license, see COPYING file.

#include <sstream>
#include <iomanip>
#include <stdio.h>

#include "amber/validation.h"
#include "structs/base58.h"
#include "chain/chain.h"
#include "json/json_spirit.h"
#include "utils/utilstrencodings.h"
#include "core/main.h" // for GetTransaction

using namespace std;
using namespace json_spirit;

/* Copied from multichainblock.cpp#FindSigner */
void FindBlockSigner(CBlock *block,unsigned char *sig,int *sig_size,uint32_t *hash_type)
{
    int key_size;
    block->vSigner[0]=0;
    
    if(mc_gState->m_NetworkParams->IsProtocolMultichain())
    {
        for (unsigned int i = 0; i < block->vtx.size(); i++)
        {
            const CTransaction &tx = block->vtx[i];
            if (tx.IsCoinBase())
            {
                for (unsigned int j = 0; j < tx.vout.size(); j++)
                {
                    mc_gState->m_TmpScript1->Clear();

                    const CScript& script1 = tx.vout[j].scriptPubKey;        
                    CScript::const_iterator pc1 = script1.begin();

                    mc_gState->m_TmpScript1->SetScript((unsigned char*)(&pc1[0]),(size_t)(script1.end()-pc1),MC_SCR_TYPE_SCRIPTPUBKEY);

                    for (int e = 0; e < mc_gState->m_TmpScript1->GetNumElements(); e++)
                    {
                        if(block->vSigner[0] == 0)
                        {
                            mc_gState->m_TmpScript1->SetElement(e);                        
                            *sig_size=255;
                            key_size=255;    
                            if(mc_gState->m_TmpScript1->GetBlockSignature(sig,sig_size,hash_type,block->vSigner+1,&key_size) == 0)
                            {
                                block->vSigner[0]=(unsigned char)key_size;
                            }            
                        }
                    }
                }
            }
        }    
    }
}


void LogInvalidBlock(CBlock& block, const CBlockIndex* pindex, std::string reason)
{
    LogPrintf("LogInvalidBlock(): %s.\n", reason);

    unsigned char sig[255];
    int sig_size;//,key_size;
    uint32_t hash_type;
    uint256 hash_to_verify;
    uint256 original_merkle_root;
    uint32_t original_nonce;
    std::vector<unsigned char> vchSigOut;
    std::vector<uint256> savedMerkleTree;
    std::string strHashType;
    std::string strSigOut;
    std::string block_hash;
    
    block.nMerkleTreeType=MERKLETREE_FULL;
    block.nSigHashType=BLOCKSIGHASH_NONE;
    
    FindBlockSigner(&block, sig, &sig_size, &hash_type);    
    if(block.vSigner[0])
    {
        switch(hash_type)
        {
            case BLOCKSIGHASH_HEADER:
                strHashType = "BLOCKSIGHASH_HEADER";
                block.nMerkleTreeType=MERKLETREE_NO_COINBASE_OP_RETURN;
                block.nSigHashType=BLOCKSIGHASH_HEADER;
                hash_to_verify=block.GetHash();
                break;
            case BLOCKSIGHASH_NO_SIGNATURE_AND_NONCE:
                strHashType = "BLOCKSIGHASH_NO_SIGNATURE_AND_NONCE";
                original_merkle_root=block.hashMerkleRoot;
                original_nonce=block.nNonce;
                
                block.nMerkleTreeType=MERKLETREE_NO_COINBASE_OP_RETURN;
                savedMerkleTree=block.vMerkleTree;
                block.hashMerkleRoot=block.BuildMerkleTree();
                block.nNonce=0;
                hash_to_verify=block.GetHash();
                
                block.hashMerkleRoot=original_merkle_root;
                block.nNonce=original_nonce;
                
                block.nMerkleTreeType=MERKLETREE_FULL;                
                if(savedMerkleTree.size())
                {
                    block.vMerkleTree=savedMerkleTree;
                }
                else
                {
                    block.BuildMerkleTree();
                }
                break;
            default:
                strHashType = "BLOCKSIGHASH_INVALID";
        }
        
        // convert sig to a hex string
        std::stringstream ss;
        ss << std::hex;
        for(int i=0;i<sig_size;++i) {
            ss << std::setw(2) << std::setfill('0') << (int)sig[i];
        }
        strSigOut = ss.str();
        block_hash = hash_to_verify.GetHex().c_str();
    }

    CPubKey miner  = pindex->kMiner;
    CBitcoinAddress minerAddress(miner.GetID());    

    LogPrintf("LogInvalidBlock(): Block sig=%s\n", strSigOut);
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
        data.push_back(Pair("block-signature", strSigOut));
        data.push_back(Pair("block-hashtype", strHashType));
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

// TODO: Merge this with txsenderisminer
bool IsMinerTx(const CTransaction& tx) 
{
    return txsenderisminer(tx);
}

// custom transaction validation entry point, for future customisation support
bool custom_accept_transacton(const CTransaction& tx, 
                              const CCoinsViewCache &inputs,
                              int offset,
                              bool accept,
                              string& reason,
                              uint32_t *replay)
{
    return true;
}
