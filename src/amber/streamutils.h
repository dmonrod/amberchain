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

namespace StreamUtils {
    unsigned int GetMinimumRelayTxFee();
    string GetAdminAddress();
}

#endif //AMBER_STREAMUTILS_H

/* AMB END */