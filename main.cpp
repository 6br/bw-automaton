#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <queue>
#include <unordered_map>
using namespace std;
///*
template <class T>
struct Node {
    T value;
    vector<Node> children;

    Node(T val) {
        this->value = val;
        vector<Node> children;
        
        this->children = children;
    }
};//*/

char base2int(char base){
  char base2int;
  switch(base){
    case '-' : base2int = 0; 
      break;
    case 'A' : base2int = 1;
      break;
    case 'T' : base2int = 2;
      break;
    case 'G' : base2int = 3;
      break;
    case 'C' : base2int = 4;
      break;
    case '#' : base2int = 5;
      break;
  }
  return base2int;
}

char int2base(char base){
  char base2int;
  switch(base){
    case 0 : base2int = '$'; 
      break;
    case 1 : base2int = 'A';
      break;
    case 2 : base2int = 'T';
      break;
    case 3 : base2int = 'G';
      break;
    case 4 : base2int = 'C';
      break;
  }
  return base2int;
}

void cytoscape(std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges){
  cout << "elements: {" << endl << "nodes: [" << endl;
  for(auto i = edges.begin(); i != edges.end(); ++i){
    cout << "{ data: { id: '" <<i->first << "', name: '" << int2base((i->first & 7))  <<"'} }," << endl;
  }
  cout << "], edges: [" << endl;
  for(auto i = edges.begin(); i != edges.end(); ++i){
    for(auto it = i->second.begin(); it != i->second.end(); ++it){
      cout << "{ data: { source: '" << i->first << "', target: '" << it->first  << "', strength: "<< pow(10, (it->second)) <<" } }," << endl;
    }
  }
  cout << "]}," << endl;
  return;
}

std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edge_set(string alignment, std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges){
  unsigned long long prev = 0;
  alignment += "#";
  for(std::string::size_type i = 0; i <= alignment.size(); ++i) {
    char base = base2int(alignment[i]);
    if(base != 0){
    unsigned long long int next = (i << 3) + (int)base;
    //cout << (int)base << " " <<next << endl;
    auto got = edges.find(prev);
      if(got == edges.end() ) {
        //cout << prev << endl;
        std::unordered_map<unsigned long long int, int> internal_edge;
        edges.insert(make_pair(prev, internal_edge));
        got = edges.find(prev);
      }
    auto got2 = got->second.find(next);
    //if 行き先のedgeがあるか? {
      if(got2 == got->second.end() ){
        got->second.insert(make_pair(next, 1));
      }else{
        got2->second++;
      }
    prev = next;
    //cout << base2int(alignment[i]) << i << endl;
   }
  }
  /*for(auto i = edges.begin(); i != edges.end(); ++i){
    cout << i->first << endl;
  }
  cout << endl;*/
  return edges;
}

std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> prefix_sorted_automaton(std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges){
  //std::priority_queue<int> queue;
  //Node<int> node(0);
  std::vector<int> isa(100);
  std::vector<int> sa(100);
  std::vector<int> radix(5, 0);
  std::vector<int> radix_pointer(5, 0);
  std::vector<std::pair<unsigned long long int, unsigned long long int>> nodes(100); //開始ノードと終端のノードのPair

  std::multimap<int, std::pair<unsigned long long int, unsigned long long int>> prefix;
  // Initialize
  for(auto i = edges.begin(); i != edges.end(); ++i){
    int value = i->first & 7;
    //count value
    radix[value]+=1;
  }
  for(auto i = 1; i<5; i++){
    radix[i] += radix[i-1];
    radix_pointer[i] = radix[i];
    cout << radix[i] << endl;
  }
  int j=0;
  for(auto i = edges.begin(); i != edges.end(); ++i, ++j){
    int value = i->first & 7;
    //count value
    nodes[j] = make_pair(i->first,i->first);
    isa[j] = radix[value];
    sa[--radix_pointer[value]] = j;
  }
  for(j=0;j<edges.size();j++){
    cerr << j << "\t" << sa[j] << "\t" << (nodes[sa[j]].first & 7) << "\t"<<isa[sa[j]] << "\t" << isa[j] << endl;
  }
  int node_size = edges.size();
  bool end = false;
  while(end == false){
		end = true;
		for(j=1; j<edges.size(); j++){
      if((nodes[sa[j]].second & 7) == (nodes[sa[j-1]].second & 7)){
        end = false;
        //nodeの延長
        auto succeeder = edges[nodes[sa[j]].second];//.second;
        int it = 0;
        for(auto s = succeeder.begin(); s != succeeder.end(); ++s, ++it){
            cerr << j<<it<< s->first << endl;
          if (it == 0){
            nodes[sa[j]].second = s->first; 
          }else{
            //nodes[sa[j]].
            isa[node_size] = isa[sa[j]];
            nodes[node_size] = make_pair(nodes[sa[j]].first, s->first);
            sa[node_size] = node_size;
            node_size++;
          }
        }
      }
    }
    for(j=0;j<node_size;j++){
      cerr << j << "\t" << sa[j] << "\t" << (nodes[sa[j]].second & 7) << "\t"<<isa[sa[j]] << "\t" << isa[j] << endl;
    }
    break;
  }
    //if(node.children[value]){
      
    //}else{
      
    //}
  //  prefix.insert(make_pair(i->first & 7, make_pair(i->first, i->first)));
  /*
  //Each of 
  while(!queue.empty()){
    int integer = queue.top();
    queue.pop();
    auto itr = prefix.equal_range(integer);//lower_bound(integer);
    for(auto i = itr.first; i != itr.second; ++i){
      if(auto next = edges.find(i->second.second) != edges.end()) {
        //i->first = i->first * 10 + next * 5
      }
    }
  }
*/
  return edges;
}

int main(){
  std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edge;// = new multimap<>;
  //std::unordered_map<unsigned long long int, std::tuple<int, int, string>> rank_suffix;
  string alignment;
  int a;
  cin >> a;
  for (int i=0;i<a;i++){
    cin >> alignment;
    edge = edge_set(alignment, edge);
  }
  edge = prefix_sorted_automaton(edge);
  cytoscape(edge);
  return 0; 
}
