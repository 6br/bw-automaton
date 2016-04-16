/*
 * File:   main.hpp
 *
 * Created on 2016/04/14
 */

using namespace std;
typedef unsigned long long int ulli;

#ifndef MAIN_HPP
#define MAIN_HPP
char base2int(char base);
char int2base(char base);
void cytoscape(std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges);
void dot(std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges);
std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edge_set(string alignment, std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges);
//std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> prefix_sorted_automaton(std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges);
std::pair<std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>>, std::unordered_map<unsigned long long int, int>> prefix_sorted_automaton(std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges);
std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> remove_edge(std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges);
std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> add_edge(std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges);
void output(bool dot_use, std::unordered_map<unsigned long long int, std::unordered_map<unsigned long long int, int>> edges);
int main(int argc, char** argv);

#endif
