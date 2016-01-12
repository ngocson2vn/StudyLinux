#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
	vector<int> ag(1);

	try {
		ag[0] = 100;
		ag.push_back(200);

		int i;
		for (i = 0; i < ag.size(); i++) {
			cout << "element " << i << ": " << ag[i] << endl;
		}

	} catch(...) {
		cout << "Unknown exception occurred!" << endl;
	}

	return 0;
}
