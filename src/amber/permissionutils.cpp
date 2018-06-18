/* AMB START */

// Amberchain code distributed under the GPLv3 license, see COPYING file.

#include "amber/permissionutils.h"

using namespace std;
using namespace json_spirit;

namespace PermissionUtils {
    string GetFirstAdminPublicKeyFromPermissions() {
        Array adminItems = GetArrayOfAdminItems();
        Object adminItemsFirstEntry = adminItems.front().get_obj();
        string firstAdminPublicKey = HexToStr(adminItemsFirstEntry[0].value_.get_str());
        
        return firstAdminPublicKey;
    }

    Array GetArrayOfAdminItems() {
        Array params;
        params.push_back("admin");
        Array adminItems = listpermissions(params, false).get_array();

        return adminItems;
    }
}

/* AMB END */