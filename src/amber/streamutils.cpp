/* AMB START */

// Amberchain code distributed under the GPLv3 license, see COPYING file.

#include "amber/streamutils.h"

using namespace std;
using namespace json_spirit;

namespace StreamUtils {
    unsigned int GetMinimumRelayTxFee() {
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

        LogPrint("ambr", "ambr-test: HEXTOSTR(%s) INT(%u)", latestMinRelayTxFeeValueString, latestMinRelayTxFeeValue); 

        return latestMinRelayTxFeeValue;
    }

    string GetAdminAddress() {
        Array streamParams;
        streamParams.push_back(STREAM_TRANSACTIONPARAMS);
        streamParams.push_back(KEY_ADMINADDRESS); 
        Array adminAddressStreamItems = liststreamkeyitems(streamParams, false).get_array();
        
        if (adminAddressStreamItems.size() == 0) {
            return PermissionUtils::GetFirstAdminAddressFromPermissions();
        }
        
        Object latestAdminAddressEntry = adminAddressStreamItems.back().get_obj();
        string latestAdminAddressValueString = HexToStr(latestAdminAddressEntry[2].value_.get_str());
        
        LogPrint("ambr", "ambr-test: HEXTOSTR(%s)", latestAdminAddressValueString); 

        return latestAdminAddressValueString;
    }
}

/* AMB END */