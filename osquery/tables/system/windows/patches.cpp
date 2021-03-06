/**
 *  Copyright (c) 2014-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under both the Apache 2.0 license (found in the
 *  LICENSE file in the root directory of this source tree) and the GPLv2 (found
 *  in the COPYING file in the root directory of this source tree).
 *  You may select, at your option, one of the above-listed licenses.
 */

#include <osquery/tables.h>

#include "osquery/core/windows/wmi.h"

namespace osquery {
namespace tables {

QueryData genInstalledPatches(QueryContext& context) {
  QueryData results;

  WmiRequest wmiSystemReq("select * from Win32_QuickFixEngineering");
  auto& wmiResults = wmiSystemReq.results();

  if (wmiResults.size() != 0) {
    Row r;

    for (const auto& item : wmiResults) {
      item.GetString("CSName", r["csname"]);
      item.GetString("HotFixID", r["hotfix_id"]);
      item.GetString("Caption", r["caption"]);
      item.GetString("Description", r["description"]);
      item.GetString("FixComments", r["fix_comments"]);
      item.GetString("InstalledBy", r["installed_by"]);
      item.GetString("InstallDate", r["install_date"]);
      item.GetString("InstalledOn", r["installed_on"]);

      results.push_back(r);
    }
  }

  return results;
}
} // namespace tables
} // namespace osquery
