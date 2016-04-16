

#ifndef BWT_H
#define	BWT_H
#include <unordered_map>
#include <vector>
using namespace std;
typedef unsigned long long int ulli;

class BWT {
public:
  BWT(std::unordered_map<ulli, unordered_map<ulli, int>> edges, unordered_map<ulli, int> ranks, bool verbose); 
  BWT(const BWT& orig);
  virtual ~BWT();
  void print();
  void find();
  string Bits2base(int base);
private:
  std::vector<int> m_table;
  std::vector<int> bwt_table;
  std::vector<int> frequency;
  bool verbose;
};

#endif	/* BWT_H */
