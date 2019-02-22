/* AMB START */

// Amberchain code distributed under the GPLv3 license, see COPYING file.

#ifndef AMBER_STREAMUTILS_H
#define AMBER_STREAMUTILS_H

#include "rpc/rpcserver.h"
#include <string>
#include "multichain/multichain.h"
#include "amber/utils.h"
#include "amber/permissionutils.h"
#include "amber/strencodings.h"
#include "utils/util.h"

using namespace std;
using namespace json_spirit;

void loginvalidblock(const CBlockIndex* pindex, std::string reason);

namespace StreamUtils {
    unsigned int GetMinimumRelayTxFee();
    string GetAdminPublicKey();
    double GetAdminFeeRatio();
    bool IsPublicAccount(string address);
    bool IsStreamExisting(string streamName);
    bool IsAuthority(string address);
}

#endif //AMBER_STREAMUTILS_H

/* AMB END */