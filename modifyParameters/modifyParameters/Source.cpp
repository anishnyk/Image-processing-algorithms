#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src, dst;

int brightness = 0;
int contrast = 0;
int const maxBrightness = 20;
int const maxContrast = 20;

void changeParameter(int, void*);

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Incorrect number of parameters" << endl;
		system("pause");
		return -1;
	}
	else
	{
		src = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
		if (!src.data)
		{
			cout << "Incorrect Image path" << endl;
			system("pause");
			return -1;
		}
	}

	// Create windows
	namedWindow("Parameters", CV_WINDOW_AUTOSIZE);

	// Create trackbars
	createTrackbar("Brightness", "Parameters",
		&brightness, maxBrightness,
		changeParameter);

	createTrackbar("Contrast", "Parameters",
		&contrast, maxContrast,
		changeParameter);

	// Default start
	changeParameter(0, 0);

	waitKey();
	return 0;
}


void changeParameter(int, void*)
{
	src.convertTo(dst, -1, (double)brightness/10, contrast);
	imshow("Parameters", dst);
	imwrite("../Assets/modifiedImage.tif", dst);
}

