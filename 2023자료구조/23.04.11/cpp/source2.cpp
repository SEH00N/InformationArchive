#include <iostream>

using namespace std;

class CParent {
public:

};

class CTest : public CParent {
public :
	void Func() {
		cout << "CTest::Func" << endl;
	}
};

int main()
{


	return 0;
}