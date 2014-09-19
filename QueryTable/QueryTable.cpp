#include "QueryTable.h"

namespace sharedon
{

int QueryTable::addToFile(const std::string& fileName, 
                          const std::string& address)
{
  WLock lockWrite(_wrMutex);
  
  if (_queryTable.count(fileName) > 0) {
    return _queryTable[fileName]->insertEntry(address);
  } else {
    CountTrie *newFile = new CountTrie;
    _queryTable[fileName] = newFile;
    return _queryTable[fileName]->insertEntry(address);
  }
}

int QueryTable::deleteFromFile(const std::string& fileName, 
                               const std::string& address)
{
  WLock lockWrite(_wrMutex);
  
  if (_queryTable.count(fileName) == 0) {
    return -1;
  } else {
    CountTrie *file = _queryTable[fileName];
    if (file->deleteEntry(address) == -1) {
      return -1;
    }
    if (file->countEntry() == 0) {
      delete file;   
    }
    return 0;
  }
}

int QueryTable::queryFile(const std::string& fileName, 
                          const std::string& address, 
                          int num, 
                          std::vector<std::string>& result)
{
  RLock lockRead(_wrMutex);
  
  if (_queryTable.count(fileName) == 0) {
    return -1;
  } else {
    return _queryTable[fileName]->findClosestEntries(address, num, result);
  }                     
}

} // namespace sharedon end
