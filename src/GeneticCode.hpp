#ifndef GENETIC_CODE_H
#define GENETIC_CODE_H

#include <string>
#include <vector>

#define N_CODONS 64

enum Nucleotide {T, C, A, G};

class Codon
{
public:
  unsigned int index;
  std::string sequence;
  std::vector<unsigned int> nucleoitdes;
  char amino_acid;
  bool is_stop;


  const unsigned int distance(Codon& b);
  const std::string to_json();
};

class GeneticCode
{

public:
  GeneticCode(std::string type);
  const Codon operator()(const unsigned int idx);                     // From index
  const Codon operator()(std::vector<unsigned int> n);                // From nucleotide numbers
  const Codon operator()(const std::string);                          // From sequence
private:
  std::string code;
  std::string type;
  Codon codons[N_CODONS+1];
  static const std::string nucleotides;
  static const std::string amino_acids;
  static const std::string standard_nuclear;

};



#endif /* GENETIC_CODE_H */
