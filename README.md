# Genetic Code

This is an Rcpp wrapper around an implementation of a codon table.

We define two classes - `Codon` and `GeneticCode`. `Codon` has `sequence`, `nucleotides`, `index`, and `amino_acid`. `GeneticCode` constructs a codon table, and can access each codon by sequence or index.

The package has `R` bindings - all the `C++` code is exposed as `R` objects.

# Installation

```
R CMD BUILD
R CMD INSTALL
```

Or, preferably `Ctrl+Shift+B` in RStudio.

# Example

``` R

g <- new(GeneticCode, "standard nuclear")

sequence <- sapply(seq(1,64), function(x) g[[x]]$sequence)

amino_acids <- sapply(seq(1,64), function(x) g[[x]]$amino_acid)
```

