#include <iostream>
using namespace std;

struct Node
{
  int val;
  Node* left;
  Node* right;
  void traverse();
  void traverseSome(int n);
  Node(int i) : val(i), left(NULL), right(NULL) {}     
};

void Node::traverse()
{  
  if (this == NULL) {
    return;
  }
  cout<<val<<endl;
  left->traverse();
  right->traverse();
}

void Node::traverseSome(int n)
{
  if (this == NULL || n == 0) {
    return;
  }
  cout<<val<<endl;
  n--;
  int n1 = n/2;
  int n2 = n/2;
  if (n%2 == 1) {
    n1++;
  }
  left->traverseSome(n1);
  right->traverseSome(n2);
}


int main()
{
  Node *head = new Node(1);
  head->left = new Node(2);
  head->right = new Node(3);
  head->left->left = new Node(4);   
  head->left->right = new Node(5);
  head->right->left = new Node(6);
  head->right->right = new Node(7);
  head->traverse();
  cout<<endl;
  head->traverseSome(6);
  system("pause");  
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

int CountTrieNode::getLeaves(std::string& s, int level, int num)
{
  CountTrieNode *prev = this;
  CountTrieNode *cur  = NULL; 
  if (prev->leafCount() > num) {
    cur = prev->getNext(c);
    cur->getLeaves(c, num);
  } else if (prev->leafCount() == num) {
    
  } else {
    
  }
}

int CountTrieNode::_getLeaves(std::string& s, int level, int num, std::vector<std::string>& result)
{
  
}



class CountTrie
{
  typedef std::pair<char, CountTrieNode* > Record;

public:
  CountTrie();
  ~CountTrie();
  
  int findEntry         (const std::string& s);
  int findClosestEntries(const std::string& s, int num, std::vector<std::string>& result);
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


