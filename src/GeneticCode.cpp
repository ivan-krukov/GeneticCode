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

        codons[c].sequence.append(1,nucleotides[i]);
        codons[c].sequence.append(1,nucleotides[j]);
        codons[c].sequence.append(1,nucleotides[k]);

        codons[c].amino_acid = code[c];

        codons[c].nucleoitdes.push_back(i);
        codons[c].nucleoitdes.push_back(j);
        codons[c].nucleoitdes.push_back(k);

        c++;
      }
    }
  }
}

const Codon GeneticCode::operator()(const unsigned int idx)
{
  if (idx < 1 || idx > 64) throw invalid_argument("Codon index should be between 1 and 64");
  return codons[idx];
}

const Codon GeneticCode::operator()(vector<unsigned int> n)
{
  if (n.size() != 3) throw invalid_argument("Nucleotide array of length 3 required");
  unsigned int idx = (n[0]*16)+(n[1]*4)+n[2]+1;
  return codons[idx];
}

const Codon GeneticCode::operator()(string s)
{
  if (s.size() != 3) throw invalid_argument("Nucleotide sequence of length 3 required");
  unsigned int idx = 1;
  idx += nucleotides.find(s[0]) * 16;
  idx += nucleotides.find(s[1]) * 4;
  idx += nucleotides.find(s[2]);
  return codons[idx];
}

// --- RCPP binding ---

// Little function for multiple dispatch
// http://lists.r-forge.r-project.org/pipermail/rcpp-devel/2010-November/001326.html
bool get_int_or_dbl_valid(SEXP* args, int nargs)
{
  if( nargs != 1 ) return false;
  unsigned int type = TYPEOF(args[0]);
  if (type != INTSXP && type != REALSXP) return false;
  return ( LENGTH(args[0]) == 1 ) ;
}

// There should be a better way or doing this
bool get_int_or_dbl_three_valid(SEXP* args, int nargs)
{
  if(nargs != 1) return false;
  unsigned int type = TYPEOF(args[0]);
  if (type != INTSXP && type != REALSXP) return false;
  return (LENGTH(args[0]) == 3);
}

bool get_string_valid(SEXP* args, int nargs)
{
  if(nargs != 1) return false;
  unsigned int type = TYPEOF(args[0]);
  if (type != STRSXP) return false;
  return (LENGTH(args[0]) == 1);
}

RCPP_EXPOSED_CLASS(Codon)
RCPP_EXPOSED_CLASS(GeneticCode)

RCPP_MODULE(GeneticCode_module)
{


  class_<Codon>("Codon")
  .field("sequence", &Codon::sequence)
  .field("amino_acid", &Codon::amino_acid)
  .field("nucleotides", &Codon::nucleoitdes)
  .field("index", &Codon::index);

  class_<GeneticCode>("GeneticCode")
  .constructor<string>()
  .method("[[", (const Codon (GeneticCode::*)(const unsigned int) )(&GeneticCode::operator()), "Codon from index", &get_int_or_dbl_valid)
  .method("[[", (const Codon (GeneticCode::*)(vector<unsigned int>) )(&GeneticCode::operator()), "Codon from nucleotides", &get_int_or_dbl_three_valid)
  .method("[[", (const Codon (GeneticCode::*)(string) )(&GeneticCode::operator()), "Codon from sequence", &get_string_valid);

}
