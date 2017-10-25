#ifndef DICO_HPP
#define DICO_HPP

#include <cmath>
#include <boost/algorithm/string.hpp>
#include <iomanip>
#include <iostream>
#include <vector>

class Letter
{
public :
	Letter(const char letter) : m_letter(letter), m_occ(0) {};
	~Letter();

	Letter *getNext(const char letter) const;
	const char getLetter() const {return m_letter;};
	const unsigned int getOcc() const {return m_occ;};
	const bool isInNext(const char letter) const;
	void addLetter(const char letter) {m_next.push_back(new Letter(letter));};
	void addOcc(){m_occ ++;};

	void print(const std::string prefix) const;

private :
	std::vector<Letter*> m_next;
	const char m_letter;
	unsigned int m_occ;
};


class Dico
{
public :
	Dico() : m_root('.'), m_nbWords(0) {};
	~Dico(){};

	void addWord(const std::string word);
	const long double getProbability(const std::string word) const;
	const unsigned int getNbWords() const {return m_nbWords;};

	void print(const std::string name) const;
	
private :
	const std::string filter(const std::string word) const;

	Letter m_root;
	unsigned int m_nbWords;
};

#endif