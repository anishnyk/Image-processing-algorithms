#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Incorrect number of parameters" << endl;
		system("pause");
		return -1;
	}
	else 
	{
		Mat src1, src2;

		src1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
		src2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);

		if (!src1.data || !src2.data)
		{
			cout << "Import error" << endl;
			system("pause");
			return -1;
		}
		else
		{
			Mat dest, final;
			double alpha = 0.5, beta;
			cout << "Enter alpha value for image blending[0-1]: " << endl;
			cin >> alpha;
			beta = 1 - alpha;

			CV_Assert(src1.type() == CV_8U && src2.type() == CV_8U);

			addWeighted(src1, alpha, src2, beta, 0.0, dest);

			cout << "Enter contrast[1.0-3.0] & brightness[0-100] values for manipulation: " << endl;
			cin >> alpha >> beta;
			final = Mat::zeros(dest.size(), dest.type());

			for (int i = 0; i < dest.rows; i++)
			{
				for (int j = 0; j < dest.cols; j++)
				{
					final.at<uchar>(i, j) = saturate_cast<uchar>(alpha * dest.at<uchar>(i, j) + beta);
				}
			}

			namedWindow("Src1", CV_WINDOW_AUTOSIZE);
			namedWindow("Src2", CV_WINDOW_AUTOSIZE);
			namedWindow("Dest", CV_WINDOW_AUTOSIZE);
			namedWindow("Final", CV_WINDOW_AUTOSIZE);

			imshow("Src1", src1);
			imshow("Src2", src2);
			imshow("Dest", dest);
			imshow("Final", final);

			waitKey();
			return 0;
		}
	}
	
	
}