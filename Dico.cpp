#include "Dico.hpp"

using namespace std;

Letter::~Letter()
{
	for(Letter* next : m_next)
		delete next;
}

const bool Letter::isInNext(const char letter) const
{
	for(Letter* next : m_next)
		if(next->getLetter() == letter) return true;

	return false;
}

Letter *Letter::getNext(const char letter) const
{
	for(Letter* next : m_next)
		if(next->getLetter() == letter) return next;
}


void Dico::addWord(const string word)
{
	Letter *pos = &m_root;
	
	for(char c : filter(word))
	{
		if(! pos->isInNext(c))
			pos->addLetter(c);

		pos->addOcc();
		pos = pos->getNext(c);
	}

	if (! pos->isInNext('\0')) pos->addLetter('\0');	
	pos = pos->getNext('\0');
	pos->addOcc();

	m_nbWords ++;
}

const long double Dico::getProbability(const string word) const
{
	const Letter* pos = &m_root;
	
	for(char c : filter(word))
		if(! pos->isInNext(c))
			return 0.0;
		else
			pos = pos->getNext(c);

	if(!pos->isInNext('\0')) 
		return 0.0;
	else 
		return (long double) pos->getNext('\0')->getOcc() / m_nbWords;
}

//TO IMPROVE !!!!
const string Dico::filter(const string word_in) const
{
	string word_out;

	for (char c : word_in)
	{
		if(c >= 'A' && c <= 'Z') word_out += c + 'a' - 'A';
		else if(c >= 'a' && c <= 'z') word_out += c;
		else if(c == '&') word_out += "and";
	}

	return word_out;
}



void Dico::print(const string name) const
{
	cout << endl << "Display of " << name << ":" << endl;
	m_root.print("");
}

void Letter::print(const string prefix) const 
{
	for(Letter* next : m_next)
		if(m_letter == '.')
			next->print(prefix);
		else
			next->print(prefix + m_letter);

	if(m_letter == '\0')
		cout << prefix << " : " << m_occ << endl;
}