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
  std::string amino_acid;
  bool is_stop;
  Codon();

  const unsigned int distance(Codon& b);
  const std::string to_json();
};

class GeneticCode
{

public:
  GeneticCode(std::string type);
  const Codon operator[](const unsigned int i);                   // From index
  const Codon operator[](std::vector<unsigned int> n);            // From nucleotide numbers
  const Codon operator[](const std::string);                      // From sequence

  // R indexing from 1
  const Codon _r_get(const unsigned int i);                       // From index
  const Codon _r_get(std::vector<unsigned int> n);                // From nucleotide numbers
  const Codon _r_get(const std::string);                          // From sequence

  // Main storage object
  std::vector<Codon> codons;

private:
  std::string code;
  std::string type;

  const unsigned int nucleotides_to_index(std::vector<unsigned int> n);
  const unsigned int sequence_to_index(const std::string);

  static const std::string nucleotides;
  static const std::string amino_acids;
  static const std::string standard_nuclear;

};

#endif /* GENETIC_CODE_H */
