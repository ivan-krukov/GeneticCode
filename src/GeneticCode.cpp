#include <Rcpp.h>
#include "GeneticCode.hpp"

using namespace Rcpp;
using namespace std;

const std::string GeneticCode::nucleotides = "TCAG";
const std::string GeneticCode::amino_acids = "ACDEFGHIKLMNPQRSTVWYZ";
const string GeneticCode::standard_nuclear = "FFLLSSSSYYZZCCZWLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG";

Codon::Codon(): index(0), sequence(3, '\0'), nucleoitdes(3), amino_acid(1, '\0')
{
}

GeneticCode::GeneticCode(string type): type(type), codons(N_CODONS)
{
  if (type == "standard nuclear") {
    code = standard_nuclear;
  } else {
    throw invalid_argument("Unrecognized genetic code type");
  }

  unsigned int c = 0;
  for (unsigned int i = T; i <= G; i++) {
    for (unsigned int j = T; j <= G; j++) {
      for (unsigned int k = T; k <= G; k++) {
        codons[c].index = c;

        codons[c].sequence[0] = nucleotides[i];
        codons[c].sequence[1] = nucleotides[j];
        codons[c].sequence[2] = nucleotides[k];

        codons[c].amino_acid[0] = code[c];

        codons[c].nucleoitdes[0] = i;
        codons[c].nucleoitdes[1] = j;
        codons[c].nucleoitdes[2] = k;

        c++;
      }
    }
  }
}

const Codon GeneticCode::operator[](const unsigned int i)
{
  return codons[i];
}

const Codon GeneticCode::operator[](vector<unsigned int> n)
{
  return codons[ nucleotides_to_index(n) ];
}

const Codon GeneticCode::operator[](string s)
{
  return codons[ sequence_to_index(s) ];
}

const Codon GeneticCode::_r_get(const unsigned int i)
{
  if (i < 1 || i > 64) throw invalid_argument("Codon index must be between 1 and 64");
  return codons[i-1];
}

const Codon GeneticCode::_r_get(vector<unsigned int> n)
{
  if (n.size() != 3) throw invalid_argument("The codon sequence should be 3 nucleotides long");
  for (int i = 0; i < 3; i++) {
    if (n[i] < 1 || n[i] > 4) { throw invalid_argument("Nucleotide indexes should be between 1 and 4"); }
    n[i] = n[i] - 1;
  }
  return codons[ nucleotides_to_index(n) ];
}

const Codon GeneticCode::_r_get(string s)
{
  if (s.size() != 3) throw invalid_argument("The codon sequence should be 3 characters long");
  if (s.find_first_not_of("TCAG") != string::npos) throw invalid_argument("The codon sequence should only contain T,C,A,G characters");
  return codons[ sequence_to_index(s) ];
}

const unsigned int GeneticCode::nucleotides_to_index(vector<unsigned int> n)
{
  return (n[0]*16)+(n[1]*4)+n[2];
}

const unsigned int GeneticCode::sequence_to_index(string s)
{
  unsigned int idx = 0;
  idx += nucleotides.find(s[0]) * 16;
  idx += nucleotides.find(s[1]) * 4;
  idx += nucleotides.find(s[2]);
  return idx;
}
