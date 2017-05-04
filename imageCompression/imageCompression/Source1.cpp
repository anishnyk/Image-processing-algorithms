#include <opencv2\opencv.hpp>
#include <opencv2\core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	if (argc != 6)
	{
		cout << "Incorrect number of parameters" << endl;
		system("pause");
		return -1;
	}
	else
	{
		cout << "Correct number of parameters" << endl;
		system("pause");
		return 0;
	}
}
