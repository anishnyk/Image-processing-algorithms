#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

void scanImageAndReduceC(Mat& I, uchar* table);
void scanImageAndReduceIterator(Mat& I, uchar* table);

int main (int argc, char* argv[])
{
	//There should be atleast 3 arguments
	if (argc < 3)
	{
		cout << "Not enough parameters" << endl;
		return -1;
	}

	//Import image from first argument with grayscale colormap if third argument is "G"
	Mat I, J, K, L;
	if (argc == 4 && strcmp(argv[3], "G"))
		I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	else
		I = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	//stringstream used to cast argument string to any other datatype
	int divideWith = 0;
	stringstream s;
	s << argv[2];
	s >> divideWith;

	//Creating the lookup table
	uchar table[256];
	for (int i = 0; i < 256; ++i)
		table[i] = (uchar)((i / divideWith) * divideWith);

	int times = 1000;

	double t = (double)getTickCount();
	for (int i = 0; i < times; i++)
	{
		//new Mat object to quantize color using [] operator
		J = I.clone();
		scanImageAndReduceC(J, table);
	}
	t = (1000 / times) * ((double)getTickCount() - t) / getTickFrequency();
	cout << "average time taken by C operator method: " << t << " ms" << endl;

	t = (double)getTickCount();
	for (int i = 0; i < times; i++)
	{
		//new Mat object to quantize color using iterators
		K = I.clone();
		scanImageAndReduceIterator(K, table);
	}
	t = (1000 / times) * ((double)getTickCount() - t) / getTickFrequency();
	cout << "average time taken by iterator method: " << t << " ms" << endl;
	
	Mat lookup(1, 256, CV_8U);
	uchar* p = lookup.data;
	for (int i = 0; i < 256; i++)
	{
		p[i] = table[i];
	}

	t = (double)getTickCount();
	for (int i = 0; i < times; i++)
	{
		//new Mat object to quantize color using iterators
		LUT(I, lookup, L);
	}
	t = (1000 / times) * ((double)getTickCount() - t) / getTickFrequency();
	cout << "average time taken by LUT method: " << t << " ms" << endl;

	////Display both images and write quantized image to the disk
	//namedWindow("I", CV_WINDOW_AUTOSIZE);
	//imshow("I", I);

	//namedWindow("J", CV_WINDOW_AUTOSIZE);
	//imshow("J", J);

	//namedWindow("K", CV_WINDOW_AUTOSIZE);
	//imshow("K", K);

	imwrite("../Assets/pepper_color_quantized_c.tif", J);
	imwrite("../Assets/pepper_color_quantized_iterator.tif", K);
	imwrite("../Assets/pepper_color_quantized_lut.tif", L);

	system("pause");
	return 0;
}

void scanImageAndReduceC(Mat& I, uchar* table)
{
	//Make sure the image is of char type
	CV_Assert(I.depth() == CV_8U);

	//Extract dimension data from Mat object
	int nChannels = I.channels();
	int nRows = I.rows;
	int nColumns = I.cols * nChannels;
	if (I.isContinuous())
	{
		nColumns *= nRows;
		nRows = 1;
	}

	//Quantizing pixels based on pixel position and value from lookup table
	for (int i = 0;  i < nRows;  i++)
	{
		uchar* p = I.ptr<uchar>(i);
		for (int j = 0; j < nColumns; j++)
		{
			p[j] = table[p[j]];
		}
	}
}

void scanImageAndReduceIterator(Mat& I, uchar* table)
{
	CV_Assert(I.depth() == CV_8U);

	int nChannels = I.channels();

	switch (nChannels)
	{
	case 1:
		for (MatIterator_<uchar> it = I.begin<uchar>(); it != I.end<uchar>(); it++)
		{
			*it = table[*it];
		}
		break;

	case 3:
		for (MatIterator_<Vec3b> it = I.begin<Vec3b>(); it != I.end<Vec3b>(); it++)
		{
			(*it)[0] = table[(*it)[0]];
			(*it)[1] = table[(*it)[1]];
			(*it)[2] = table[(*it)[2]];
		}
		break;

	default:
		break;
	}
}