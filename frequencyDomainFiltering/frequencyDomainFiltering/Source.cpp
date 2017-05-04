#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Incorrect number of parameters" << endl;
		system("pause");
		return -1;
	}
	else
	{
		Mat source = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
		if (source.empty())
		{
			cout << "Image not found" << endl;
			system("pause");
			return -1;
		}
		else
		{
			Mat paddedSource, paddedSourceAround;
			int m = getOptimalDFTSize(source.rows);
			int n = getOptimalDFTSize(source.cols);

			copyMakeBorder(source, paddedSource, 0, m - source.rows, 0, n - source.cols, BORDER_CONSTANT, Scalar::all(0));
			copyMakeBorder(source, paddedSourceAround, (m - source.rows) / 2, (m - source.rows) / 2, (n - source.cols) / 2, (n - source.cols) / 2, BORDER_CONSTANT, Scalar::all(0));

			Mat complexDest;
			Mat planes[] = { Mat_<float>(paddedSource), Mat::zeros(paddedSource.size(), CV_32F) };
			merge(planes, 2, complexDest);
			
			dft(complexDest, complexDest);
			split(complexDest, planes);


			namedWindow("real", CV_WINDOW_AUTOSIZE);
			namedWindow("imaginary", CV_WINDOW_AUTOSIZE);
			namedWindow("source", CV_WINDOW_AUTOSIZE);

			imshow("real", planes[0]);
			imshow("imaginary", planes[1]);
			imshow("source", source);

			waitKey();
			return 0;
		}
	}
}