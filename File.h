
template <typename Owner>
class FileOwnerCollection {
  FileOnwerCollection(string& filename);
  ~FileOnwerCollection();
  int addOwner            (const Owner& x);
  int deleteOwner         (const Owner& x);
  int searchOwner         (const Owner& x, std::vector<Owner> res);
private:
  string                  fileName;  
  int                     ownerNum;
  OwnerCollection<Owner>  ownerCol;
};

#define SUCCEED  0
#define ERROR   -1

class CountTrie
{
public:
  CountTrie();
  ~CountTrie();
  
  int findEntry         (const std::string& s);
  int findClosestEntries(const std::string& s, int num, std::vector<string> result);
  int insertEntry       (const std::string& s);
  int deleteEntry       (const std::string& s);
  
private:
  CountTrieNode *head;
};

int CountTrie::findEntry(const std::string& s)
{
  int len = s.size();  
  if (len == 0) {
    return ERROR;
  }
  CountTrieNode *tmp = head;
  for (int i = 0; i < len; i++) {
    tmp = tmp->children[s[i]];
    if (tmp == NULL) {
      return ERROR;
    }
    if (tmp->isLeaf == true) {
      if (i == len-1) {
        return SUCCEED;
      } else {
        continue;
      }
    }
  }
}

int CountTrie::insertEntry(const std::string& s)
{
  int len = s.size();
  if (len == 0) {
    return ERROR;
  }
  Count
}





#include <stack>
#include <list>
#include <iostream>
#include <utility>
#include <string>
#include <alogrithm>
#include <functional>

namespace sharedon
{
      
class CountTrieNode
{
  friend class CountTrie;
  typedef std::pair<char, CountTrieNode* > Record;
  
private:
  CountTrieNode() : isLeaf(true), leafCount(0) { }
  ~CountTrieNode();
  
  CountTrie* getNext     (char c);
  int        addRecord   (char c);
  int        deleteRecord(char c);
  
  bool isLeaf     ()           { return _isLeaf; }
  void setLeaf    (bool state) { isLeaf = bool; return; }
  int  leafCount  ()           { return _leafCount;}
  void addCount   ()           { leafCount++; return; }
  void minusCount ()           { leafCount--; return; }
  int  getCount   ()           { return leafCount; }
  int  getLeaves  (int num) 
  
private:
  static bool isRecordEqualTo(Record& rec, char c) { return rec.first == c; }
  
private:
  bool              _isLeaf;
  int               _leafCount;
  std::list<Record> recordList;       
};

CountTrieNode* CountTrieNode::getNext(char c)
{
  std::list<Record>::iterator it = std::find_if(recordList.begin(), recordList.end(), std::bind2nd(isRecordEqualTo, c));
  if (it == recordList.end())
    return NULL;
  return *it.second;
}

int CountTrieNode::addRecord(char c)
{
  CountTrieNode *newNode = new CountTrieNode;
  Record newRecord = std::makepair(c, newNode);
  recordList.push_back(newRecord);
  return 0;
}

int CountTrieNode::deleteRecord(char c)
{
  std::list<Record>::iterator it = std::find_if(recordList.begin(), recordList.end(), std::bind2nd(isRecordEqualTo, c));
  if (it == recordList.end()) {
    return -1;
  } else {
    recordList.erase(it);
    return 0;  
  }
}

int CountTrieNode::getLeaves(char c, int num)
{
  CountTrieNode *prev = this;
  CountTrieNode *cur  = NULL; 
  if (prev->leafCount() > num) {
    cur = prev->getNext(c);
    cur->getLeaves(c, num);
  }
  
  
  
}


class CountTrie
{
  typedef std::pair<char, CountTrieNode* > Record;

public:
  CountTrie();
  ~CountTrie();
  
  int findEntry         (const std::string& s);
  int findClosestEntries(const std::string& s, int num, std::vector<string>& result);
  int insertEntry       (const std::string& s);
  int deleteEntry       (const std::string& s);
  
private:
  void destory();
  
private:
  std::string    id;
  CountTrieNode *root;
 
};

bool CountTrie::findEntry(const std::string& s)
{
  int sz = s.size();
  if (sz == 0) {
    return false;
  }
  
  CountTrieNode *prev = root;
  CountTrieNode *cur  = NULL;  
  
  for (int i = 0; i < sz; i++) {
    cur = prev->getNext(s[i]);
    if (cur == NULL) {
      return false;
    } else {
      prev = cur;
    }
  }
  
  if (cur->isLeaf()) {
    return true;
  } else {
    return false;
  } 
}

int CountTrie::insertEntry(const std::string& s)
{
  if (findEntry(s)) {
    return -1;
  }
  
  CountTrieNode *prev = root;
  CountTrieNode *cur  = NULL;
  int sz = s.size();
  int insertPos = 0;
  
  for (int i = 0; i < sz; i++) {
    cur = prev->getNext(s[i]);
    if (cur == NULL) {
      insertPos = i;
      break;
    } else {
      prev->addCount();
      prev = cur;
    }
  }
  
  for (int i = insertPos; i < sz; i++) {
    prev->addRecord(s[i]);
    prev->setLeaf(false);
    prev->addCount();
  }
  
  return 0;
}

int CountTrie::deleteEntry(const std::string& s)
{
  if (findEntry(s) == false) {
    return -1;
  }
  
  int sz = s.size();
  CountTrieNode *prev = root;
  CountTrieNode *cur  = NULL;
  
  for (int i = 0; i < sz; i++) {
    cur = prev->getNext(s[i])
    prev->minusCount();
    if (prev->getCount() == 0) {
      delete prev;
    }
    if (cur->getCount() == 1) {
      prev->deleteRecord(s[i]);
    }
  }
  
  delete cur;
  
  return 0;
}

} //namspace share end

