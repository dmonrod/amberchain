/* AMB START */

// Amberchain code distributed under the GPLv3 license, see COPYING file.

#ifndef AMBER_CONSTANTS_H
#define AMBER_CONSTANTS_H

#include <string>
#include <map>
#include <vector>

#define STREAM_AUTHNODES            "authoritynodes"
#define STREAM_AUTHREQUESTS         "authorityrequests"
#define STREAM_TRANSACTIONPARAMS    "transactionparams"
#define STREAM_RECORDS              "records"
#define STREAM_ANNOTATEDRECORDS     "annotatedrecords"
#define KEY_TRANSACTIONFEE          "min-relay-tx-fee"
#define KEY_ADMINADDRESS            "admin-address"
#define KEY_ADMINFEERATIO           "admin-fee-ratio"

using namespace std;

/*

To get the streams relevant to a permission:
    vector<std::string> streams = StreamConsts::streamsPerPermission.at("admin");
    for(std::vector<std::string>::iterator it = streams.begin(); it != streams.end(); ++it) {
        std::string stream_name = *it;
        throw runtime_error(stream_name);
    }

 */
struct StreamConsts 
{
    static map< string, vector<string> > create_map()
    {
        map< string, vector<string> > m;

		vector<string> admin_streams;
		admin_streams.push_back(STREAM_AUTHNODES);
        admin_streams.push_back(STREAM_TRANSACTIONPARAMS);
		m["admin"] = admin_streams;

		vector<string> mine_streams;
        mine_streams.push_back(STREAM_RECORDS);
        mine_streams.push_back(STREAM_ANNOTATEDRECORDS);
		m["mine"] = mine_streams;		
        return m;
    }
    static const map< string, vector<string> > streamsPerPermission;
};

string SampleFunction();

#endif

/* AMB END */