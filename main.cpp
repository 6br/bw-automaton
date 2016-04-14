#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <queue>
#include <unordered_map>
#include <list>
using namespace std;
typedef unsigned long long int uuli;
#define debug(x) cout<<#x<<": "<<x<<endl
#define DEBUG(x) cout<<#x<<": "<<x<<endl;

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
  std::vector<int> isa(15);
  std::vector<int> sa_builder(100);
  std::list<int> sa;
  std::vector<int> radix(5, 0);
  std::vector<int> radix_pointer(5, 0);
  std::vector<std::pair<unsigned long long int, unsigned long long int>> nodes(100); //開始ノードとその次のノードと終端のノードのPair
  std::vector<std::pair<ulli, ulli, ulli>> nodes_tuple(100);

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
    nodes_tuple[j] = make_tuple(i->first, 0, i->first)
    isa[j] = radix[value];
    sa_builder[--radix_pointer[value]] = j;
  }
  for(j=0;j<edges.size();j++){
    sa.push_back(sa_builder[j]);
  }
  j=0;
  for(auto itr=sa.begin();j<edges.size();j++,++itr){
    cerr << j << "\t" << *itr << "\t" << (nodes[*itr].first & 7) << "\t"<<isa[*itr] << "\t" << isa[j] << endl;
  }
  int node_size = edges.size();
  bool end = false;
  while(end == false){
		end = true;
    j = 1;
		for(auto itr = ++sa.begin(); itr != sa.end(); ++itr,j++){
        cout << j << " " << isa[*itr] << sa.size() <<endl;
        //if((nodes[*(itr--)].second & 7) == (nodes[*(itr++)].second & 7) || (j != sa.size()-1 && ((nodes[*(++itr)].second & 7) == (nodes[*(--itr)].second & 7)) )){
        if(j != 1 && isa[*itr--] == isa[*itr++] || (j < isa.size()-1 && (isa[*++itr] == isa[*--itr]))){
        cout << j << " " << isa[*itr] << sa.size() <<endl;
        end = false;
        //nodeの延長
        auto succeeder = edges[nodes[*itr].second];//.second;
        int it = 0;
        for(auto s = succeeder.begin(); s != succeeder.end(); ++s, ++it){
            cerr << j<<" "<<it<<" " << s->first << endl;
          if (it == 0){
            nodes[*itr].second = s->first; 
          }else{
            //nodes[sa[j]].
            std::unordered_map<unsigned long long int, int> internal_edge;
            auto it = edges[nodes[*itr].first].begin();//.begin();
            //if(it++==edges[nodes[*itr].first].end()){--it;}

            cout << it->first << it->second << endl;
            internal_edge.insert(make_pair(it->first, it->second));
            int i;
            for(i=1; i<10; i++){
              cout << "aa"<< (i << 10) + nodes[*itr].first  << endl;
              if(edges.find((i << 10)+nodes[*itr].first) == edges.end())break;
            }
            edges.insert(make_pair((i<<10) + nodes[*itr].first, internal_edge));
            
            nodes[node_size] = make_pair(nodes[*itr].first, s->first);
            isa[node_size] = isa[*itr];
            itr = sa.insert(itr, node_size);
            node_size++;itr++;
            
          }
        }
      }
    }/*
    for(j=0;j<node_size;j++){
      cerr << j << "\t" << sa[j] << "\t" << (nodes[sa[j]].second & 7) << "\t"<<isa[sa[j]] << "\t" << isa[j] << endl;
    }*/
    if(end == false){
      j=1;
      for(auto itr = ++sa.begin();itr!=sa.end();j++,++itr){
        cerr << j << "\t" << *itr << "\t" << (nodes[*itr].second & 7) << "\t"<<isa[*itr] << "\t" << isa[j] << endl;
      }
      j = 1;
      auto prev_isa = isa[*sa.begin()];
      std::multimap<int, int> bucket; //O(log n)になってしまうので、基数ソートしたいが連結リスト表現だとが大きいか。
      for(auto itr = ++sa.begin();itr!=sa.end();j++,++itr){
        cout << isa[*itr] << prev_isa << endl;
        if((isa[*itr]) == prev_isa){
           bucket.insert(make_pair(nodes[*itr].second & 7, *itr)); 
        }else{ 
          //stackをどこかで処理
          if(bucket.size()>1){
            std::pair<int,int> prev_first = make_pair(0,0);
            j--;
				    for(auto bkt = bucket.rbegin(); bkt != bucket.rend(); bkt++,j--){
              cout << bkt->first <<" "<< bkt->second << " " << j << " " << isa[*(itr)] <<endl;
              auto j2 = (bkt->first != prev_first.first) ? j: prev_first.second;//{isa[*--itr] = j;}else{auto stab = isa[*itr]; isa[*--itr] = stab;} //要検討
              //auto j2 = (bkt->first != isa[*(itr)]) ? j: isa[*itr];//{isa[*--itr] = j;}else{auto stab = isa[*itr]; isa[*--itr] = stab;} //要検討
              *(--itr) = bkt->second;
              isa[*itr] = j2;
              prev_first = make_pair(bkt->first, j2);
            }
            for(int k=0; k<bucket.size(); k++) {itr++;j++;}
            j++;
          }
          bucket.clear();//bucketを空にする    
          prev_isa = isa[*itr];
          isa[*itr] = j;
          bucket.insert(make_pair(nodes[*itr].second & 7, *itr)); 
        }
      }
      // 最後に、残ったバケツを処理する。
      auto itr = sa.rbegin(); 
          if(bucket.size()>1){
            //j = j - bucket.size();
            std::pair<int,int> prev_first = make_pair(0,0);
				    for(auto bkt = bucket.rbegin(); bkt != bucket.rend(); bkt++,j--){
              cerr <<j<<" "<< bkt->first <<" "<< bkt->second << isa[*(itr)] <<endl;
              auto j2 = (bkt->first != prev_first.first) ? j: prev_first.second;//{isa[*--itr] = j;}else{auto stab = isa[*itr]; isa[*--itr] = stab;} //要検討
              *(itr) = bkt->second;
              isa[*itr++] = j2; //要検討
              prev_first = make_pair(bkt->first, j2);
            }
          }

      j = 1;
      for(auto itr = ++sa.begin();itr!=sa.end();j++,++itr){
        cerr << j << "\t" << *itr << "\t" << (nodes[*itr].second & 7) << "\t"<<isa[*itr] << "\t" << isa[j] << endl;
      }
    }
    //break;
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
