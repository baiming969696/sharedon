
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
