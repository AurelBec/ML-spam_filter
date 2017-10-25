#ifndef CLASSIFIER_HPP
#define CLASSIFIER_HPP

#include <fstream>
#include <algorithm>

#include "Dico.hpp"

#define TOKENIZERS "\t ,.,!()?"

class Classifier
{
public :
	Classifier(std::ifstream &file, const unsigned int percent);
	~Classifier(){};

	void test(const unsigned int nbTests) const;

private :
	void train(const unsigned int percent);
	const unsigned int runClassification(const unsigned int n, const unsigned int from, const unsigned int to) const;
	const bool isClassedAsSpam(std::vector<std::string> &msg) const;

	std::ifstream &m_file;
	Dico m_dicoSpam;
	Dico m_dicoHam;
	unsigned int m_total;
	unsigned int m_sizeTrain;
	unsigned int m_sizeTest;
	unsigned int m_nbSpam;
	unsigned int m_nbHam;
	long double m_probS;
	long double m_probH;

};

#endif