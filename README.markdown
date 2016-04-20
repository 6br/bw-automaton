bw-automaton -- bwt for multiple alignment
===

[![Build Status](https://drone.io/github.com/6br/bw-automaton/status.png)](https://drone.io/github.com/6br/bw-automaton/latest)

Convert the multiple-alignment result to prefix-sorted-automaton for Burrows Wheeler Transformation

## Description
To visualize or map faster, we often use graph expression of reference genome. This program converts multiple alignment result to automaton, which is small and understandable expression.

![Picture](https://raw.githubusercontent.com/6br/bw-automaton/master/sample/test.png)

![Picture](https://raw.githubusercontent.com/6br/bw-automaton/master/sample/result.png)

## Dependency
* GCC
* C++11
* Graphviz(Optional)

## Install
```bash
git clone https://github.com/6br/bw-automaton.git
cd bw-automaton
./configure
make
```

## Usage
```
$ bw_automaton < sample/sample.txt
```

Sample of input is following.

```
4
GACGTA-CTG
GACGTA---G
GATGTA-CTG
GAC-TACCTG
```

And results are exported as Cytoscape.js style, So you can visualize on Web. Please see sample folder.

### Flags

* v: verbose(for debugging)
* d: export as a dot style
* m: export reverse-deterministic-automaton
* b: export BWT table
* c: export with colour(by 4 line)

You should use these options as below.

```
$ bw_automaton -dm < sample.txt | dot -Tpng -o sample.png
```

## Notion
* find(BWT) hasn't implemented yet. But you can easily find or locate from BWT table.

## License
MIT

## Reference
* Ferragina, P., Luccio, F., Manzini, G., & Muthukrishnan, S. (2009). Compressing and indexing labeled trees, with applications. Journal of the ACM, 57(1), 1–33. http://doi.org/10.1145/1613676.1613680
* Sirén, J., Välimäki, N., & Mäkinen, V. (2014). Indexing graphs for path queries with applications in genome research. IEEE/ACM Transactions on Computational Biology and Bioinformatics, 11(2), 375–388. http://doi.org/10.1109/TCBB.2013.2297101
