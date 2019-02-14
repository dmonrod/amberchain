/* AMB START */

// Amberchain code distributed under the GPLv3 license, see COPYING file.

#include "amber/streamutils.h"
#include "structs/base58.h"
#include "chain/chain.h"
#include "json/json_spirit.h"
#include "utils/utilstrencodings.h"

using namespace std;
using namespace json_spirit;

namespace StreamUtils {
    unsigned int GetMinimumRelayTxFee() {
        if (!IsStreamExisting(STREAM_TRANSACTIONPARAMS)) {
            return MIN_RELAY_TX_FEE;
        }

        Array streamParams;
        streamParams.push_back(STREAM_TRANSACTIONPARAMS);
        streamParams.push_back(KEY_TRANSACTIONFEE); 
        Array minRelayTxFeeStreamItems = liststreamkeyitems(streamParams, false).get_array();
        
        if (minRelayTxFeeStreamItems.size() == 0) {
            return MIN_RELAY_TX_FEE;
        }
        
        Object latestMinRelayTxFeeEntry = minRelayTxFeeStreamItems.back().get_obj();
        string latestMinRelayTxFeeValueString = HexToStr(latestMinRelayTxFeeEntry[2].value_.get_str());
        
        unsigned int latestMinRelayTxFeeValue = atoi(latestMinRelayTxFeeValueString.c_str());

        LogPrint("ambr", "ambr-test: min-relay-tx-fee HEXTOSTR(%s) INT(%u)\n", latestMinRelayTxFeeValueString, latestMinRelayTxFeeValue);

        return latestMinRelayTxFeeValue;
    }

    string GetAdminPublicKey() {
        string noAdminPublicKey = "0";

        if (!IsStreamExisting(STREAM_TRANSACTIONPARAMS)) {
            return noAdminPublicKey;
        }

        Array streamParams;
        streamParams.push_back(STREAM_TRANSACTIONPARAMS);
        streamParams.push_back(KEY_ADMINPUBLICKEY);
        Array adminPublicKeyStreamItems = liststreamkeyitems(streamParams, false).get_array();
        
        if (adminPublicKeyStreamItems.size() == 0) {
            // return PermissionUtils::GetFirstAdminPublicKeyFromPermissions();
            return noAdminPublicKey;
        }

        Object latestAdminPublicKeyEntry = adminPublicKeyStreamItems.back().get_obj();
        string latestAdminPublicKeyValueString = HexToStr(latestAdminPublicKeyEntry[2].value_.get_str());
        
        LogPrint("ambr", "ambr-test: admin-address HEXTOSTR(%s) \n", latestAdminPublicKeyValueString);

        return latestAdminPublicKeyValueString;
    }

    double GetAdminFeeRatio() {
        double adminFeeRatioValue = 0;

        if (!IsStreamExisting(STREAM_TRANSACTIONPARAMS)) {
            return adminFeeRatioValue;
        }

        Array streamParams;
        streamParams.push_back(STREAM_TRANSACTIONPARAMS);
        streamParams.push_back(KEY_ADMINFEERATIO);
        Array adminFeeRatioStreamItems = liststreamkeyitems(streamParams, false).get_array();

        if (adminFeeRatioStreamItems.size() == 0) {
            return adminFeeRatioValue;
        }

        Object adminFeeRatioEntry = adminFeeRatioStreamItems.back().get_obj();
        string adminFeeRatioValueString = HexToStr(adminFeeRatioEntry[2].value_.get_str());

        adminFeeRatioValue = atof(adminFeeRatioValueString.c_str());

        LogPrint("ambr", "ambr-test: admin-fee-ratio HEXTOSTR(%s) DOUBLE(%f)", adminFeeRatioValueString, adminFeeRatioValue);

        return adminFeeRatioValue;
    }

    bool IsPublicAccount(string address) {
        if (!IsStreamExisting(STREAM_TRANSACTIONPARAMS)) {
            return false;
        }

        Array streamParams;
        streamParams.push_back(STREAM_TRANSACTIONPARAMS);
        streamParams.push_back(KEY_PUBLICACCOUNT);
        Array streamItems = liststreamkeyitems(streamParams, false).get_array();
        
        if (streamItems.size() == 0) {
            // return PermissionUtils::GetFirstAdminPublicKeyFromPermissions();
            return false;
        }

        Object latestEntry = streamItems.back().get_obj();
        string latestValueString = HexToStr(latestEntry[2].value_.get_str());
        
        LogPrint("ambr", "ambr-test: public-account HEXTOSTR(%s) \n", latestValueString);

        return strcmp(latestValueString.c_str(), address.c_str()) == 0;
    }

	bool IsAuthority(string address) { 
	    
		bool isAuthority = haspermission(address,"mine");
		if (isAuthority || !IsStreamExisting(STREAM_AUTHNODES) ) return isAuthority;

		Array params;
		params.push_back(STREAM_AUTHNODES);
        std::string AUTH_ID = string(ID_AUTHORITY);
		params.push_back(AUTH_ID+"_"+address);
		//get all entries from the badgeissuer stream with the key specific to the address to be checked
		Array results = liststreamkeyitems(params, false).get_array();
		
		if (results.size() > 0) {
			
			BOOST_FOREACH(const Value& authority, results) {
				Object authorityObject = authority.get_obj();

				std::string hex_data = authorityObject[2].value_.get_str();
				std::string json_data = HexToStr(hex_data);
				Value data;
				read_string(json_data, data);
				Object dataObject = data.get_obj();
				
				std::string authorityPermission = dataObject[0].value_.get_str();
				// LogPrint("ambr", "ambr-test: admin-address HEXTOSTR(%s) \n", latestAdminPublicKeyValueString);
				if (strcmp(authorityPermission.c_str(), "grant") == 0) {
					isAuthority = true;
				}
				else {
					isAuthority = false;
				}
			}
		}	
        return isAuthority;
	}	
	
	
	

    bool IsStreamExisting(string streamName) {
        try {
            Array streamParams;
            streamParams.push_back(streamName);
            Array streamResults = liststreams(streamParams, false).get_array();
            return true;
        }
        catch (...) {
            return false;
        }

    }

}

/* AMB END */

