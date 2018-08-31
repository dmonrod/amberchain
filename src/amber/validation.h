/* AMB START */

// Amberchain code distributed under the GPLv3 license, see COPYING file.

#ifndef AMBER_VALIDATION_H
#define AMBER_VALIDATION_H

#include "core/main.h"
#include "rpc/rpcserver.h"
#include <string>
#include "multichain/multichain.h"
#include "amber/utils.h"
#include "amber/permissionutils.h"
#include "amber/strencodings.h"
#include "utils/util.h"

using namespace std;
using namespace json_spirit;

void LogInvalidBlock(CBlock& block, const CBlockIndex* pindex, std::string reason);
bool IsMinerTx(const CTransaction& tx);
bool custom_accept_transacton(const CTransaction& tx, 
                              const CCoinsViewCache &inputs,
                              int offset,
                              bool accept,
                              std::string& reason,
                              uint32_t *replay);

#endif //AMBER_VALIDATION_H

/* AMB END */