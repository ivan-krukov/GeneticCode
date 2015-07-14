#include <Rcpp.h>
#include "GeneticCode.hpp"
#include "StochasticTunneling.hpp"
using namespace Rcpp;
using namespace std;

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
    .method("[[", (const Codon (GeneticCode::*)(const unsigned int) )(&GeneticCode::_r_get), "Codon from index", &get_int_or_dbl_valid)
    .method("[[", (const Codon (GeneticCode::*)(vector<unsigned int>) )(&GeneticCode::_r_get), "Codon from nucleotides", &get_int_or_dbl_three_valid)
    .method("[[", (const Codon (GeneticCode::*)(string) )(&GeneticCode::_r_get), "Codon from sequence", &get_string_valid);

}
