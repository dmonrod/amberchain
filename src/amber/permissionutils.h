/* AMB START */

// Amberchain code distributed under the GPLv3 license, see COPYING file.

#ifndef AMBER_PERMISSIONUTILS_H
#define AMBER_PERMISSIONUTILS_H

#include "rpc/rpcserver.h"
#include <string>
#include "multichain/multichain.h"
#include "amber/strencodings.h"
#include "utils/util.h"

using namespace std;
using namespace json_spirit;

namespace PermissionUtils {
    string GetFirstAdminAddressFromPermissions();
    Array GetArrayOfAdminItems();
}

#endif //AMBER_PERMISSIONUTILS_H

/* AMB END */