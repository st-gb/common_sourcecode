#pragma once

#include <set> //class std::set
#include <string> //class std::string

template<typename member_type> class NodeTrie;

enum
{
  NotConnectedToInternet,
  ConnectedToInternet,
  alreadyConnectedViaThisAdapter,
  alreadyDisconnectedViaThisAdapter
};

  bool InternetConnectionExists(
    const char * ar_p_chAdaptersToSkip [],
    unsigned uiNumAdaptersToSkip,
    //const
    NodeTrie<BYTE> & c_r_nodetrieIPadapterName2connectionState,
    bool & bConnectionStateForAtLeats1AdapterChanged,
    std::set<std::string> & r_std_set_std_stringAdapterDescription
    );
