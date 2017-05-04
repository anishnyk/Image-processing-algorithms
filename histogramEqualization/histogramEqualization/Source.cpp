#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	// Create source and destination Mat objects and name for the named windows
	Mat src, dst;
	char* srcWindow = "Source";
	char* dstWindow = "Destination";

	// Check for number of command line arguments
	if (argc != 2)
	{
		cout << "Incorrect number of arguments" << endl;
		system("pause");
		return -1;
	}
	else
	{
		src = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
		if (!src.data)
		{
			cout << "Incorrect image path" << endl;
			system("pause");
			return -1;
		}
	}

	// Perform histogram equalization
	equalizeHist(src, dst);
	
	// 256 bins of the histogram from 0 to 255
	int histSize = 256;

	// Range of intensity values from 0 to 255
	float range[] = { 0, 256 };
	const float* histRange = { range };

	// Uniform size for all bins and histogram to be cleared each time before display
	bool uniform = true;
	bool accumulate = false;

	// Create the histogram Mat objects for soure and destination
	Mat histSrc, histDst;

	// Calculate the histograms for the source Mat object
	calcHist(&src, 1, 0, Mat(), histSrc, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&dst, 1, 0, Mat(), histDst, 1, &histSize, &histRange, uniform, accumulate);

	// Create the histogram image for display
	int histWidth = 512; 
	int histHeight = 400;
	int binWidth = cvRound((double)histWidth / histSize);

	Mat histImage(histHeight, histWidth, CV_8UC3, Scalar(0, 0, 0));

	// Normalize the values of the histogram images from 0 to number of rows = 256
	normalize(histSrc, histSrc, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(histDst, histDst, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	// Create the histogram diagram
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(binWidth * (i - 1), histHeight - histSrc.at<float>(i - 1)), Point(binWidth * i, histHeight - histSrc.at<float>(i)), Scalar(255, 0, 0), 1, 8, 0);
		line(histImage, Point(binWidth * (i - 1), histHeight - histDst.at<float>(i - 1)), Point(binWidth * i, histHeight - histDst.at<float>(i)), Scalar(0, 0, 255), 1, 8, 0);
	}

	/* Display both the histograms
	 Blue line - source histogram
	 Red line - destination histogram*/
	namedWindow("Source & Destination Histograms", CV_WINDOW_AUTOSIZE);
	imshow("Source & Destination Histograms", histImage);

	// Display both the images in separate windows
	namedWindow(srcWindow, CV_WINDOW_AUTOSIZE);
	imshow(srcWindow, src);

	namedWindow(dstWindow, CV_WINDOW_AUTOSIZE);
	imshow(dstWindow, dst);

	//Write the equalized image and the histograms to the disk
	imwrite("../Assets/equalized.tif", dst);
	imwrite("../Assets/histogram.tif", histImage);

	waitKey();
	return 0;
}