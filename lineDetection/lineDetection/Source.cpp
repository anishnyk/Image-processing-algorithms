#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat source, sourceEasy, sourceMed, sourceHard, noise;
Mat lapResult, sobelResult_x, sobelResult_y, sobelResult, dest, cannyResult;
int lowThreshold;
int const max_lowThreshold = 300;
int ratio = 3;
char* window_name = "Edge Map";
vector<Vec2f> lines;
vector<Vec4i> linesProb;

void CannyThreshold(int, void*)
{
	Canny(sourceEasy, dest, lowThreshold, lowThreshold*ratio);
	
	// Using Canny's output as a mask, we display our result
	cannyResult = Scalar::all(0);

	source.copyTo(cannyResult, dest);
	imshow(window_name, cannyResult);
	imwrite("../Assets/cannyResult.jpg", cannyResult);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Incorrect number of arguments" << endl;
		system("pause");
		return -1;
	}
	else
	{
		source = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

		if (source.empty())
		{
			cout << "Image not found" << endl;
			system("pause");
			return -1;
		}
		else
		{
			noise = Mat(source.size(), source.type());
			
			randn(noise, 0, 1);
			sourceEasy = source + noise;

			randn(noise, 0, 25);
			sourceMed = source + noise;

			randn(noise, 0, 100);
			sourceHard = source + noise;

			/*namedWindow("Easy source", CV_WINDOW_AUTOSIZE);
			imshow("Easy source", sourceEasy);
			
			namedWindow("Medium source", CV_WINDOW_AUTOSIZE);
			imshow("Medium source", sourceMed);
			
			namedWindow("Hard source", CV_WINDOW_AUTOSIZE);
			imshow("Hard source", sourceHard);*/

			imwrite("../Assets/sourceEasy.jpg", sourceEasy);
			imwrite("../Assets/sourceMed.jpg", sourceMed);
			imwrite("../Assets/sourceHard.jpg", sourceHard);

			//double t = (double)getTickCount();
			//for (int i = 0; i < 100; i++)
			//{
			//	//Laplacian(sourceEasy, lapResult, CV_16S, 3);
			//	//Laplacian(sourceMed, lapResult, CV_16S, 3);
			//	//Laplacian(sourceHard, lapResult, CV_16S, 3);

			//	/*Sobel(sourceEasy, sobelResult_x, CV_16S, 1, 0);
			//	Sobel(sourceEasy, sobelResult_y, CV_16S, 0, 1);
			//	addWeighted(sobelResult_x, 0.5, sobelResult_y, 0.5, 0, sobelResult);*/
			//	/*Sobel(sourceMed, sobelResult_x, CV_16S, 1, 0);
			//	Sobel(sourceMed, sobelResult_y, CV_16S, 0, 1);
			//	addWeighted(sobelResult_x, 0.5, sobelResult_y, 0.5, 0, sobelResult);*/
			//	/*Sobel(sourceHard, sobelResult_x, CV_16S, 1, 0);
			//	Sobel(sourceHard, sobelResult_y, CV_16S, 0, 1);
			//	addWeighted(sobelResult_x, 0.5, sobelResult_y, 0.5, 0, sobelResult);*/

			//	/*Canny(sourceEasy, dest, 25, 75);
			//	cannyResult = Mat(Scalar::all(0));
			//	source.copyTo(cannyResult, dest);*/
			//	/*Canny(sourceMed, dest, 124, 372);
			//	cannyResult = Mat(Scalar::all(0));
			//	source.copyTo(cannyResult, dest);*/
			//	Canny(sourceHard, dest, 198, 594);
			//	/*cannyResult = Mat(Scalar::all(0));
			//	source.copyTo(cannyResult, dest);*/

			//	//HoughLines(dest, lines, 1, CV_PI / 180, 100, 0, 0);
			//	HoughLinesP(dest, linesProb, 1, CV_PI / 180, 50, 50, 10);
			//}
			//t = 10 * ((double)getTickCount() - t) / getTickFrequency();
			//cout << "Average time for 1 trial = " << t << " ms" << endl;

			/*namedWindow(window_name, CV_WINDOW_AUTOSIZE);
			createTrackbar("Min: ", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
			CannyThreshold(lowThreshold, 0);*/
			
			/*convertScaleAbs(lapResult, lapResult);
			namedWindow("Laplacian result", CV_WINDOW_AUTOSIZE);
			imshow("Laplacian result", lapResult);
			imwrite("../Assets/laplacianResult.jpg", lapResult);*/

			/*convertScaleAbs(sobelResult, sobelResult);
			namedWindow("Sobel result", CV_WINDOW_AUTOSIZE);
			imshow("Sobel result", sobelResult);
			imwrite("../Assets/sobelResult.jpg", sobelResult);*/

			/*namedWindow("Canny result", CV_WINDOW_AUTOSIZE);
			imshow("Canny result", cannyResult);
			imwrite("../Assets/cannyResult.jpg", cannyResult);*/

			/*for (size_t i = 0; i < lines.size(); i++)
			{
			float rho = lines[i][0], theta = lines[i][1];
			Point pt1, pt2;
			double a = cos(theta), b = sin(theta);
			double x0 = a*rho, y0 = b*rho;
			pt1.x = cvRound(x0 + 1000 * (-b));
			pt1.y = cvRound(y0 + 1000 * (a));
			pt2.x = cvRound(x0 - 1000 * (-b));
			pt2.y = cvRound(y0 - 1000 * (a));
			line(dest, pt1, pt2, Scalar(0, 0, 255), 3, CV_8U);
			}*/
					
			/*for (size_t i = 0; i < lines.size(); i++)
			{
				Vec4i l = linesProb[i];
				line(dest, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_8U);
			}

			namedWindow("Hough result", CV_WINDOW_AUTOSIZE);
			imshow("Hough result", dest);
			imwrite("../Assets/houghResult.jpg", dest);*/

			waitKey();
			return 0;
		}
	}
}