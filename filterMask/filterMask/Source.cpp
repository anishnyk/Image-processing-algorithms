#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

void sharpen(const Mat& Input, Mat& Result, int intensity = 5);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Not enough parameters" << endl;
		system("pause");
		return -1;
	}
	
	Mat I, J, K;
	I = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (!I.data)
	{
		cout << "Image not found" << endl;
		system("pause");
		return -1;
	}

	double t = (double)getTickCount();
	for (int i = 0; i < 100; i++)
	{
		sharpen(I, J, 5);
	}
	t = 10 * ((double)getTickCount() - t) / getTickFrequency();
	cout << "Average time for 1 trial = " << t << " ms" << endl;

	Mat kern = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

	t = (double)getTickCount();
	for (int i = 0; i < 100; i++)
	{
		filter2D(I, K, I.depth(), kern);
	}
	t = 10 * ((double)getTickCount() - t) / getTickFrequency();
	cout << "Average time for 1 trial = " << t << " ms" << endl;

	imwrite("../Assets/peppers_color_filtered_1.tif", J);
	imwrite("../Assets/peppers_color_filtered_2.tif", K);

	system("pause");
	return 0;
}

void sharpen(const Mat& Input, Mat& Result, int intensity)
{
	CV_Assert(Input.depth() == CV_8U);

	Result.create(Input.size(), Input.type());
	int nRows = Input.rows;
	int nColumns = Input.cols;
	int nChannels = Input.channels();
	
	for (int i = 1; i < nRows - 1; i++)
	{
		const uchar* previous = Input.ptr<uchar>(i - 1);
		const uchar* current = Input.ptr<uchar>(i);
		const uchar* next = Input.ptr<uchar>(i + 1);

		uchar* p = Result.ptr<uchar>(i);

		for (int j = nChannels; j < nChannels * (nColumns - 1); j++)
		{
			*p++ = saturate_cast<uchar>(intensity * current[j] - current[j - nChannels] - current[j + nChannels] - previous[j] - next[j]);
		}
	}

	Result.row(0).setTo(Scalar(0));
	Result.row(nRows - 1).setTo(Scalar(0));
	Result.col(0).setTo(Scalar(0));
	Result.col(nColumns - 1).setTo(Scalar(0));
}