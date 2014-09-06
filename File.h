
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

