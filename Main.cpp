#include "Classifier.hpp"

using namespace std;

/*Input file have to use this format :
ham lorem ipsum dolor
ham sit amet
spam foo bar
...

exemple can be found here : http://archive.ics.uci.edu/ml/datasets/SMS+Spam+Collection#
*/


int main(int argc, char *argv[])
{
	srand(time(NULL));
	cout << "- WARNING: No dealing with unknown words! -" << endl;

	ifstream dataFile;

	if (argc > 1)
		dataFile.open(argv[1]);
	else
		dataFile.open("SMSSpamCollection");

	if (dataFile.fail())
	{
		cout << "Unable to open file " << argv[1] << endl;
		cout << "Use ./EXE PATH_TO_FILE to choose an other one" << endl;
		return EXIT_FAILURE;
	}

	Classifier spamFilter(dataFile, 70);
	spamFilter.test(100);

	dataFile.close();
	return EXIT_SUCCESS;
}
