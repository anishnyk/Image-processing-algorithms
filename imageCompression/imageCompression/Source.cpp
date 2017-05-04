#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

uchar codeArray[5][100];
Mat sourceArray[5];

void runCoding(uchar* codeElem, Mat source)
{
	//Make sure the image is of char type
	//CV_Assert(source.depth() == CV_8U);

	cout << "Image imported" << endl;

	namedWindow("Image", CV_WINDOW_AUTOSIZE);
	imshow("Image", source);
	waitKey(0);

	int row = source.rows;
	int col = source.cols;

	if (source.isContinuous())
	{
		col *= row;
		row = 1;
	}
	
	int k = 0;
	
	for (int i = 0; i < row; i++)
	{
		uchar* rowElem = source.ptr<uchar>(i);
		if (codeElem[k] != rowElem[0])
		{
			k += 2;
			codeElem[k] = rowElem[0];
			codeElem[k + 1] = 1;
		}
		else
		{
			codeElem[k + 1]++;
		}
		for (int j = 1; j < col; j++)
		{
			if (codeElem[k] != rowElem[j])
			{
				k += 2;
				codeElem[k] = rowElem[j];
				codeElem[k + 1] = 1;
			}
			else
			{
				codeElem[k + 1]++;
			}
		}
	}
}

void printMatrix(uchar* arrayElem, int size)
{
	cout << "Hello" << endl;
	for (int i = 0;  i < size;  i++)
	{
		cout << arrayElem[i] + " ";
	}
}

int main(int argc, char* argv[])
{
	if (argc != 6)
	{
		cout << "Incorrect number of arguments" << endl;
		system("pause");
		return -1;
	}
	else
	{
		for (size_t i = 0; i < 5; i++)
		{
			sourceArray[i] = imread(argv[i + 1], CV_LOAD_IMAGE_GRAYSCALE);
		}
		for (size_t i = 0; i < 5; i++)
		{
			if (!sourceArray[i].data)
			{
				cout << "Incorrect image path" << endl;
				system("pause");
				return -1;
			}
			else
			{
				Mat source = (Mat_<uchar>(3, 3) << 1, 0, 0, 0, 1, 0, 0, 0, 1);

				//runCoding(&codeArray[i][0], sourceArray[i]);
				runCoding(codeArray[i], source);
				printMatrix(codeArray[i], sizeof(codeArray[i]));
			}
		}
		system("pause");
		return 0;
	}
}