
#include "bwt.h"
#include <unordered_map>
#include <vector>
#include <bitset>
#include <sstream>
#include <iostream>
typedef unsigned long long int ulli;

BWT::BWT(std::unordered_map<ulli, unordered_map<ulli, int>> edges, std::unordered_map<ulli, int> ranks, bool verbose){
  std::vector<int> m(ranks.size());
  std::vector<int> bwt(ranks.size(), 0);
  std::vector<int> freq(ranks.size(), 0);
  if(verbose){
    for(auto k = ranks.begin(); k != ranks.end(); ++k){
      cerr << k->first << "\t" << k->second << "a" << endl;
    }
  }
  for(auto i = edges.begin(); i != edges.end(); ++i){
    m[ranks[i->first]] = (1 << i->second.size() - 1); 
    for(auto it = i->second.begin(); it != i->second.end(); ++it){
      bwt[ranks[it->first]] = bwt[ranks[it -> first]] | (1 << ((i->first & 7) - 1));
      freq[ranks[it->first]] += it -> second;
      if(verbose)cerr << it->first << "\t" << ranks[it->first] << "\t" << i->first << "\t" << (i->first & 7) << endl;
    }
  }
  m_table = m;
  bwt_table = bwt;
  frequency = freq;
}

BWT::BWT(const BWT& orig) {
}

BWT::~BWT() {
}

void BWT::print() {
  for(int j = 0; j < bwt_table.size(); j++){
    cout << Bits2base(bwt_table[j]) << "\t" << static_cast<std::bitset<8>>(m_table[j]) << "\t" << frequency[j] << endl;
  }
}

void BWT::find() {
  //Stab
}

string BWT::Bits2base(int base){
  stringstream ss;
  if(base & (1<<0)) ss << "A";
  if(base & (1<<1)) ss << "C";
  if(base & (1<<2)) ss << "G";
  if(base & (1<<3)) ss << "T";
  return ss.str();
}

