#include <opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("D:\\1.png");  //����Լ�ͼ���·�� 
	imshow("��ʾͼ��", image);
	waitKey(0);
	return 0;
}