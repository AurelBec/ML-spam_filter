#include "Classifier.hpp"

using namespace std;
using namespace boost;

Classifier::Classifier(ifstream &file, const unsigned int percentUseForTraining)
: m_total(0)
, m_sizeTrain(0)
, m_sizeTest(0)
, m_nbSpam(0)
, m_nbHam(0)
, m_probS(0.0)
, m_probH(0.0)
, m_dicoSpam()
, m_dicoHam()
, m_file(file)
{
	string line;
	file.seekg (0);
	while(getline(file, line)) m_total++;

	// cout << "Building Classifier: " << endl; 
	// cout << setw(6) << setfill(' ') << m_total << " example" << ((m_total > 1) ? "s": "") << " found" << endl;

	train(percentUseForTraining);
}

void Classifier::train(const unsigned int percentUseForTraining)
{
	cout << endl;
	cout << "Training Classifier with "<< percentUseForTraining << "% of the set:" << endl;

	string line;
	m_sizeTrain = m_total * percentUseForTraining / 100;
	m_sizeTest = m_total - m_sizeTrain;

	vector<string> msg;
	char *token;
	
	m_file.clear();
	m_file.seekg (0);
	for (int i = 0; i < m_sizeTrain; ++i)
	{
		getline(m_file, line);
		split(msg, line, is_any_of(TOKENIZERS));

		if(msg.front() == "ham")
		{
			m_nbHam ++;
			msg.erase(msg.begin());
			for (string word : msg)
				m_dicoHam.addWord(word); 
		}
		else if(msg.front() == "spam")
		{
			m_nbSpam ++;
			msg.erase(msg.begin());
			for (string word : msg)
				m_dicoSpam.addWord(word); 
		}
	}

	cout << setw(6) << setfill(' ') << m_sizeTrain << " example" << ((m_sizeTrain > 1) ? "s": "") << " used for training" << endl;
	cout << setw(6) << setfill(' ') << m_nbSpam << " spam" << ((m_nbSpam > 1) ? "s": "") << " found" << endl;
	cout << setw(6) << setfill(' ') << m_dicoSpam.getNbWords() << " word" << ((m_dicoHam.getNbWords() > 1) ? "s": "") << " in the spam dictionnary" << endl;
	cout << setw(6) << setfill(' ') << m_nbHam << " ham" << ((m_nbHam > 1) ? "s": "") << " found" << endl;
	cout << setw(6) << setfill(' ') << m_dicoHam.getNbWords() << " word" << ((m_dicoSpam.getNbWords() > 1) ? "s": "") << " in the ham dictionnary" << endl;

	m_probS = (double) m_nbSpam / m_sizeTrain;
	m_probH = 1.0 - m_probS;
}

void Classifier::test(const unsigned int nbTests) const
{
	cout << endl;
	cout << "Starting evalution:" << endl;

	unsigned int n, nbgoodResults;

	//Testing in the known set
	if( nbTests > m_sizeTrain) cout << " - WARNING: Not enough known examples. Use " << m_sizeTrain << " instead of " << nbTests << endl;
	n = min(nbTests, m_sizeTrain);
	cout << " Accuracy with " << n << " known examples:" << endl;
	runClassification(n, 0, m_sizeTrain);


	//Testing in the unknown set
	if( nbTests > m_sizeTest) cout << " - WARNING: Not enough unknown examples. Use " << m_sizeTest << " instead of " << nbTests << endl;
	n = min(nbTests, m_sizeTest);
	cout << endl << " Accuracy with " << n << " unknown examples:" << endl;
	runClassification(n, m_sizeTrain, m_total);
}

const void Classifier::runClassification(const unsigned int n, const unsigned int from, const unsigned int to) const
{
	uint TP = 0, FP = 0, TN = 0, FN = 0;

	string line;
	vector<string> msg;	
	vector<int> id;
	for (int i = 0; i < to - from; ++i) id.push_back(i + from);
	random_shuffle(id.begin(), id.end());

	for (int t = 0; t < n; ++t)
	{		
		m_file.clear();
		m_file.seekg(0);
		for (int i = 0; i < id[t]; ++i)
			getline(m_file, line);

		split(msg, line, is_any_of(TOKENIZERS));

		if(msg.front() == "spam")
			if(isClassedAsSpam(msg)) TP ++;
			else FN ++;
		else
			if(isClassedAsSpam(msg)) FP ++;
			else TN ++;
	}


	cout << "  Precision: " << (double) TP / (TP + FP) << endl;
	cout << "  Recall: " << (double) TP / (TP + FN) << endl;
	cout << "  False Positive Rate: " << (double) FP / (FP + TN) << endl;
	cout << "  Accuracy: \033[01;34m" << (double) (TP + TN) / (TP + FN + TN + FP) << "\033[00m" << endl;
	cout << "  F-measure: \033[01;34m" << (double) 2 * TP / ( 2 * TP + FP + FN) << "\033[00m" << endl;

	//return nbOk;
}

const bool Classifier::isClassedAsSpam(vector<string> &msg) const
{
	long double pSpam = 1.0;
	long double pHam = 1.0;

	msg.erase(msg.begin());
	for(string word : msg)
	{
		pSpam *= m_dicoSpam.getProbability(word) * m_probS;
		pHam *= m_dicoHam.getProbability(word) * m_probH;
	}

	return (bool) (pSpam > pHam);
}
