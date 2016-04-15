#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <map>
#include <queue>
#include <unordered_map>
#include <list>
#include <algorithm>
#include "main.h"
using namespace std;

typedef unsigned long long int ulli;
#define debug(x) cout<<#x<<": "<<x<<endl
#define DEBUG(x) cout<<#x<<": "<<x<<endl;
bool verbose = false;

/*
template <class T>
struct Node {
    T value;
    vector<Node> children;

    Node(T val) {
        this->value = val;
        vector<Node> children;
        
        this->children = children;
    }
};*/

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

void dot(std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges){
  cout << "digraph G {" << endl;
  cout << "graph [rankdir = LR]" << endl;
  for(auto i = edges.begin(); i != edges.end(); ++i){
    cout << i->first << "[label=\"" << int2base((i->first & 7))  <<"\"];" << endl;
  }
  for(auto i = edges.begin(); i != edges.end(); ++i){
    for(auto it = i->second.begin(); it != i->second.end(); ++it){
      cout << i->first << "->" << it->first  << " [weight = "<< it->second <<"];" << endl;
    }
  }
  cout << "}" << endl;
  return;
}

std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edge_set(string alignment, std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges){
  unsigned long long prev = 0;
  alignment += "#";
  for(std::string::size_type i = 0; i <= alignment.size(); ++i) {
    char base = base2int(alignment[i]);
    if(base != 0){
    unsigned long long int next = (i << 3) + (int)base;
    auto got = edges.find(prev);
      if(got == edges.end() ) {
        std::unordered_map<unsigned long long int, int> internal_edge;
        edges.insert(make_pair(prev, internal_edge));
        got = edges.find(prev);
      }
    auto got2 = got->second.find(next);
      if(got2 == got->second.end() ){
        got->second.insert(make_pair(next, 1));
      }else{
        got2->second++;
      }
    prev = next;
   }
  }
  return edges;
}

std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> prefix_sorted_automaton(std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges){
  std::vector<int> isa;
  std::vector<int> sa_builder(100);
  std::list<int> sa;
  std::vector<int> radix(5, 0);
  std::vector<int> radix_pointer(5, 0);
  std::vector<std::tuple<ulli, ulli, ulli>> nodes_tuple(100);

  // Initialize
  for(auto i = edges.begin(); i != edges.end(); ++i){
    int value = i->first & 7;
    //count value
    radix[value]+=1;
  }
  for(auto i = 1; i<5; i++){
    radix[i] += radix[i-1];
    radix_pointer[i] = radix[i];
    //cout << radix[i] << endl;
  }
  int j=0;
  for(auto i = edges.begin(); i != edges.end(); ++i, ++j){
    int value = i->first & 7;
    //count value
    nodes_tuple[j] = make_tuple(i->first, 0, i->first);
    isa.push_back(radix[value]);
    sa_builder[--radix_pointer[value]] = j;
  }
  for(j = 0; j < edges.size(); j++){
    sa.push_back(sa_builder[j]);
  }
  if(verbose){
    j = 0;
    for(auto itr=sa.begin();j<edges.size();j++,++itr){
      cerr << j << "\t" << *itr << "\t" << (get<0>(nodes_tuple[*itr]) & 7) << "\t" << isa[*itr] << "\t" << isa[j] << endl;
    }
  }
  int node_size = edges.size();
  bool end = false;
  while(end == false){
		end = true;
    j = 1;
		for(auto itr = ++sa.begin(); itr != sa.end(); ++itr,j++){
        if(verbose) cerr << j << " " << isa[*itr] << sa.size() <<endl;
        if(j != 1 && isa[*itr--] == isa[*itr++] || (j < isa.size()-1 && (isa[*++itr] == isa[*--itr]))){
        end = false;
        //Extend nodes.
        auto succeeder = edges[get<2>(nodes_tuple[*itr])];
        int it = 0;
        for(auto s = succeeder.begin(); s != succeeder.end(); ++s, ++it){
            if(verbose) cerr << j<<" "<<it<<" " << s->first << endl;
          if (it == 0){
            get<2>(nodes_tuple[*itr]) = s->first; 
          }else{
            std::unordered_map<unsigned long long int, int> internal_edge;
            auto it = edges[get<0>(nodes_tuple[*itr])].begin();
            if(verbose) cerr << it->first << it->second << endl;
            auto from = get<1>(nodes_tuple[*itr]);
            if(from == 0){
              internal_edge.insert(make_pair(s->first, s->second));
              from = s->first;
            }else{
              internal_edge.insert(make_pair(get<1>(nodes_tuple[*itr]), s->second));
            }
            int i;
            for(i = 1; i < 10; i++){
              if(verbose) cerr << "aa" << (i << 10) + get<0>(nodes_tuple[*itr])  << endl;
              if(edges.find((i << 10)+get<0>(nodes_tuple[*itr])) == edges.end())break;
            }
            edges.insert(make_pair((i << 10) + get<0>(nodes_tuple[*itr]), internal_edge));
            
            nodes_tuple[node_size] = make_tuple(get<0>(nodes_tuple[*itr]), from, s->first);
            isa[node_size] = isa[*itr];
            itr = sa.insert(itr, node_size);
            node_size++; itr++;
          }
        }
      }
    }
    if(end == false){
      if(verbose){
        j = 1;
        for(auto itr = ++sa.begin();itr!=sa.end();j++,++itr){
          cerr << j << "\t" << *itr << "\t" << (get<2>(nodes_tuple[*itr]) & 7) << "\t"<<isa[*itr] << "\t" << isa[j] << endl;
        }
      }
      j = 1;
      auto prev_isa = isa[*sa.begin()];
      std::multimap<int, int> bucket; //O(log n)になってしまうので、基数ソートしたいが連結リスト表現だとが大きいか。
      for(auto itr = ++sa.begin(); itr!=sa.end(); j++, ++itr){
        if(verbose) cerr << isa[*itr] << prev_isa << endl;
        if((isa[*itr]) == prev_isa){
           bucket.insert(make_pair(get<2>(nodes_tuple[*itr]) & 7, *itr)); 
        }else{ 
          if(bucket.size()>1){
            std::pair<int,int> prev_first = make_pair(0,0);
            j--;
				    for(auto bkt = bucket.rbegin(); bkt != bucket.rend(); bkt++,j--){
              if(verbose) cerr << bkt->first <<" "<< bkt->second << " " << j << " " << isa[*(itr)] << endl;
              auto j2 = (bkt->first != prev_first.first) ? j: prev_first.second;
              *(--itr) = bkt->second;
              isa[*itr] = j2;
              prev_first = make_pair(bkt->first, j2);
            }
            for(int k=0; k<bucket.size(); k++) {itr++;j++;}
            j++;
          }
          bucket.clear(); 
          prev_isa = isa[*itr];
          isa[*itr] = j;
          bucket.insert(make_pair(get<2>(nodes_tuple[*itr]) & 7, *itr)); 
        }
      }
      // 最後に、残ったバケツを処理する。
      auto itr = sa.rbegin(); 
          if(bucket.size()>1){
            std::pair<int,int> prev_first = make_pair(0,0);
				    for(auto bkt = bucket.rbegin(); bkt != bucket.rend(); bkt++,j--){
              if(verbose) cerr <<j<<" "<< bkt->first <<" " << bkt->second << " "  << isa[*(itr)] << " " << endl;
              auto j2 = (bkt->first != prev_first.first) ? j : prev_first.second;
              *(itr) = bkt->second;
              isa[*itr++] = j2;
              prev_first = make_pair(bkt->first, j2);
            }
          }
      if(verbose) {
        j = 1;
        for(auto itr = ++sa.begin();itr!=sa.end();j++,++itr){
          cerr << j << "\t" << *itr << "\t" << (get<2>(nodes_tuple[*itr]) & 7) << "\t"<<isa[*itr] << "\t" << isa[j] << endl;
        }
      }
    }
  }
  return edges;
}

std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> add_edge(std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges){
  std::vector<std::unordered_map<ulli,int>::iterator> rmlist;
  for(auto i = edges.begin(); i != edges.end(); ++i){
    for( auto j = i->second.begin(); j != i->second.end(); ++j){ 
      for(int k = (i->first >> 10); k<10; k++){
        if(verbose)cerr << "aa" << (k << 10) + j->first << endl;
        if(edges.find((k << 10)+j->first) == edges.end()) break;
        i->second.insert(make_pair((k << 10)+j->first,j->second ));
      }
    }
  }

  for(auto i = edges.begin(); i != edges.end(); ++i){
    for( auto j = i->second.begin(); j != i->second.end(); ++j){ 
      for(int k = (i->first >> 10)+1; k<10; k++){
        auto s = edges.find((k << 10) + i->first - ((i->first >> 10 ) << 10));
        if(verbose) cerr << i->first << (k<<10)-((i -> first >> 10 ) << 10)+i->first << endl;
        if(s == edges.end())break;
        for(auto l = s->second.begin(); l != s->second.end(); ++l){
          if(verbose) cerr << "a" << i->first << " " << (k << 10) + i->first << " " << j->first << " " << l->first << endl;
          if(l->first == j->first){if(verbose) cerr << j->first << endl; rmlist.push_back(j);}
        }
      }
    }
    for(int w = 0; w < rmlist.size(); w++){
      if(w == 0 || rmlist[w] != rmlist[w-1]){
        i->second.erase(rmlist[w]);
      }
    }
    rmlist.clear();
  }
  return edges;
}

void output(bool dot_use, unordered_map<ulli, unordered_map<ulli, int>> edges){
  if(dot_use){
    dot(edges);
  } else {
    cytoscape(edges);
  }
  return;
}

int main(int argc, char** argv){
  bool dot_use = false;
  bool midstream = false;
  if(argc >= 2 && strstr(argv[1], "v") != NULL){
    verbose = true;
  }
  if(argc >= 2 && strstr(argv[1], "d") != NULL){
    dot_use = true;
  }
  if(argc >= 2 && strstr(argv[1], "m") != NULL){
    midstream = true;
  }
  std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges;
  string alignment;
  int a;
  cin >> a;
  for (int i=0;i<a;i++){
    cin >> alignment;
    edges = edge_set(alignment, edges);
  }
  if(midstream)output(dot_use, edges);
  edges = prefix_sorted_automaton(edges);
  edges = add_edge(edges);
  if(!midstream)output(dot_use, edges);
  //bwt(edge, ranks);
  return EXIT_SUCCESS; 
}
