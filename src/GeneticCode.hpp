#ifndef GENETIC_CODE_H
#define GENETIC_CODE_H

#include <string>

#define N_CODONS 64

enum Nucleotide {T, C, A, G};

class Codon
{
public:
  unsigned int index;
  char sequence[3+1];
  Nucleotide nucleoitdes[3];
  char amino_acid;
  bool is_stop;

  const unsigned int distance(Codon& b);
  const std::string to_json();
};

class GeneticCode
{

public:
  GeneticCode(std::string type);
  const Codon operator()(const unsigned int i);
  // const Codon operator()(const char sequence[4]);
  // const Codon operator()(const Nucleotide nucleotides[3]);
private:
  std::string code;
  std::string type;
  Codon codons[N_CODONS+1];
  static const std::string nucleotides;
  static const std::string amino_acids;
  static const std::string standard_nuclear;

};



#endif /* GENETIC_CODE_H */
