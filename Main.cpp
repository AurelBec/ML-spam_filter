#include "Classifier.hpp"
#define DEFAULT_PATH "SMSSpamCollection"

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

	ifstream dataFile;

	if (argc > 1)
		dataFile.open(argv[1]);
	else
		dataFile.open(DEFAULT_PATH);

	if (dataFile.fail())
	{
		cout << "Unable to open " << ((argc == 1)? "the default file" : argv[1]) << endl;
		cout << "Use " << argv[0] << " PATH_TO_FILE to choose an other one" << endl;
		return EXIT_FAILURE;
	}

	cout << "- WARNING: No dealing with unknown words! -" << endl;
	Classifier spamFilter(dataFile, 70);
	spamFilter.test(1000);

	dataFile.close();
	return EXIT_SUCCESS;
}
