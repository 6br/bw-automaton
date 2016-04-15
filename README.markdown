bwt-automaton
===

Convert the multiple-alignment result to prefix-sorted-automaton for Burrows Wheeler Transformation

## Description
To visualize or map faster, we often use graph expression of reference genome.

## Dependency
* GCC
* C++11
* Graphviz(Optional)

## Install
```bash
git clone https://github.com/6br/bwt_automaton.git
cd 
./configure
make
```

## Usage
```
main -i < sample.txt
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

You should use these options as below.

```
main -dm < sample.txt | dot -Tpng -o sample.png
```

## Notion
* BWT hasn't implemented yet.

## License
MIT

## Reference
* Ferragina, P., Luccio, F., Manzini, G., & Muthukrishnan, S. (2009). Compressing and indexing labeled trees, with applications. Journal of the ACM, 57(1), 1–33. http://doi.org/10.1145/1613676.1613680
* Sirén, J., Välimäki, N., & Mäkinen, V. (2014). Indexing graphs for path queries with applications in genome research. IEEE/ACM Transactions on Computational Biology and Bioinformatics, 11(2), 375–388. http://doi.org/10.1109/TCBB.2013.2297101
