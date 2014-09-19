#include "./CountTrie.h"
#include <boost/thread.hpp>  
#include <boost/thread/mutex.hpp>     
#include <map>
#include <string>  
#include <iostream>  

namespace sharedon
{
          
typedef boost::shared_mutex         WRMutex;
typedef boost::unique_lock<WRMutex> WLock;
typedef boost::shared_lock<WRMutex> RLock;

class QueryTable
{
  typedef std::map<std::string, CountTrie* >           Table;
  typedef std::map<std::string, CountTrie* >::iterator TableIter;
  
public:     
  QueryTable();
  ~QueryTable();

  int addToFile     (const std::string& fileName, const std::string& address);
  int deleteFromFile(const std::string& fileName, const std::string& address);   
  int queryFile     (const std::string& fileName, const std::string& address, 
                     int num, std::vector<std::string>& result);

private:
  Table   _queryTable;
  WRMutex _wrMutex;
  
};

} // namespace sharedon end


