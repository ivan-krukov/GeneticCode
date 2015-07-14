#include <Rcpp.h>
#include "GeneticCode.hpp"

using namespace Rcpp;
using namespace std;

const std::string GeneticCode::nucleotides = "TCAG";
const std::string GeneticCode::amino_acids = "ACDEFGHIKLMNPQRSTVWYZ";
const string GeneticCode::standard_nuclear = "FFLLSSSSYYZZCCZWLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG";

GeneticCode::GeneticCode(string type): type(type)
{
  if (type == "standard nuclear") {
    code = standard_nuclear;
  } else {
    throw invalid_argument("Unrecognized genetic code type");
  }

  unsigned int c = 1;
  for (unsigned int i = T; i <= G; i++) {
    for (unsigned int j = T; j <= G; j++) {
      for (unsigned int k = T; k <= G; k++) {
        codons[c].index = c;

        codons[c].sequence[0] = nucleotides[i];
        codons[c].sequence[1] = nucleotides[j];
        codons[c].sequence[2] = nucleotides[k];
        codons[c].sequence[3] = '\0';

        codons[c].amino_acid = code[c];

        codons[c].nucleoitdes[0] = (Nucleotide)i;
        codons[c].nucleoitdes[1] = (Nucleotide)j;
        codons[c].nucleoitdes[2] = (Nucleotide)k;

        c++;
      }
    }
  }
}

const Codon GeneticCode::operator()(const unsigned int i)
{
  if (i < 1 || i > 64) throw invalid_argument("Codon index should be between 1 and 64");
  Rcout << i << " " << codons[i].sequence << endl;
  return codons[i];
}

// --- RCPP binding ---

RCPP_EXPOSED_CLASS(Codon)
RCPP_EXPOSED_CLASS(GeneticCode)

RCPP_MODULE(GeneticCode_module)
{
  class_<Codon>("Codon")
  // .default_constructor()
  // .field("sequence", &Codon::sequence)
  // .field("amino_acid", &Codon::amino_acid)
  // .field("nucleotides", &Codon::nucleoitdes)
  .field("index", &Codon::index);

  class_<GeneticCode>("GeneticCode")
  .constructor<string>()
  .method("[[", &GeneticCode::operator());

}
