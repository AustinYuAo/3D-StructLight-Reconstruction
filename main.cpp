
#include <vtkSmartPointer.h>
#include <vtkPlaneSource.h>
#include <vtkCylinderSource.h>
#include <vtkCubeSource.h>
#include <vtkAxesActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkMatrix4x4.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSphereSource.h>
#include<vtkProperty.h>
#include<random>
#include<time.h>
#include <io.h>
#include <vtkAppendPolyData.h>
#include<vtkPLYWriter.h>

#include "mainwindow.h"
#include <QApplication>

#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

//Rect g_rectangle;
//std::vector<Rect> rectanglelist;
//std::vector<vector<int> > colorlist;
//bool g_bDrawingBox=false;
//RNG	 g_rng(1234);
//void DrawRectangle(Mat & image, Rect rect,int b,int g,int r)
//{
//	rectangle(image, rect.tl(), rect.br(), Scalar(b, g, r));
//	
//}
//void On_MouseHandle(int event, int x, int y, int flags, void * param)
//{
//	switch (event)
//	{
//	case EVENT_MOUSEMOVE:
//	{
//		if (g_bDrawingBox)
//		{
//			g_rectangle.width = x - g_rectangle.x;
//			g_rectangle.height = y - g_rectangle.y;
//		}
//		break;
//	}
//	case EVENT_LBUTTONDOWN:
//	{
//		g_bDrawingBox = true;
//		std::cout << g_bDrawingBox;
//		g_rectangle = Rect(x, y, 0, 0);
//		break;
//	}
//	case EVENT_LBUTTONUP:
//	{
//		g_bDrawingBox = false;
//		if (g_rectangle.width < 0)
//		{
//			g_rectangle.x += g_rectangle.width;
//			g_rectangle.width *= -1;
//		}
//		if (g_rectangle.height < 0)
//		{
//			g_rectangle.y += g_rectangle.height;
//			g_rectangle.height *= -1;
//		}
//		Rect temrectangle = g_rectangle;
//		vector<int> color;
//		for (int i = 0; i < 3; i++)
//		{
//			color.push_back(g_rng.uniform(0, 255));
//		}
//		//int color[3] = { g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255) };
//		std::cout <<"color"<< color[0] << " " << color[1] << " " << color[2] << endl;
//		rectanglelist.push_back(temrectangle);
//		colorlist.push_back(color);
//	}
//	default:
//		break;
//	}
//
//}

////��ʴ���Ͳ�������ʾ��
//Mat g_srcImage, g_dstImage;//ԭʼͼ��Ч��ͼ
//int g_nTrackbarNumer = 0;//0��ʾ��ʴerode, 1��ʾ����dilate
//int g_nStructElementSize = 3; //�ṹԪ��(�ں˾���)�ĳߴ�
//void Process();//���ͺ͸�ʴ�Ĵ�����
//void on_TrackbarNumChange(int, void *);//�ص�����
//void on_ElementSizeChange(int, void *);//�ص�����


//Mat rotateImage1(Mat img, int degree,int mode=1)
//{
//	degree = -degree;
//	double angle = degree  * CV_PI / 180.; // ����  
//	double a = sin(angle), b = cos(angle);
//	int width = img.cols;
//	int height = img.rows;
//	int width_rotate ;
//	int height_rotate;
//	if (mode == 0)
//	{
//		width_rotate = int(pow(2, 0.5)*(width / 2 + height / 2) / 2);
//		height_rotate = int(pow(2, 0.5)*(width / 2 + height / 2) / 2);
//	}
//	else if (mode == 1||mode==2)
//	{
//		width_rotate = int(height * fabs(a) + width * fabs(b));
//		height_rotate = int(width * fabs(a) + height * fabs(b));
//	}
//
//	//��ת����map
//	// [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
//	// [ m3  m4  m5 ] ===>  [ A21  A22   b2 ]
//	float map[6];
//	Mat map_matrix = Mat(2, 3, CV_32F, map);
//	// ��ת����
//	Point2f center = Point2f(width / 2, height / 2);
//	map_matrix = getRotationMatrix2D(center, degree, 1.0);
//	std::cout << (width_rotate - width) / 2 << " " << (height_rotate - height) / 2 << std:: endl;
//	std::cout << map_matrix << std::endl;
//	map_matrix.at<double>(0,2) += (width_rotate - width) / 2;
//	map_matrix.at<double>(1, 2) += (height_rotate - height) / 2;
//	std::cout << map_matrix << std::endl;
//	Mat img_rotate;
//	//��ͼ��������任
//	//CV_WARP_FILL_OUTLIERS - ����������ͼ������ء�
//	//�������������������ͼ��ı߽��⣬��ô���ǵ�ֵ�趨Ϊ fillval.
//	//CV_WARP_INVERSE_MAP - ָ�� map_matrix �����ͼ������ͼ��ķ��任��
//	warpAffine(img, img_rotate, map_matrix, Size(width_rotate, height_rotate), INTER_LINEAR, BORDER_CONSTANT, 0);
//
//	if (mode == 2)
//	{
//		Range Rangex = Range(int(width*fabs(a)), height_rotate - int(width*fabs(a)) );
//		Range Rangey = Range(int(height*fabs(a)), width_rotate - int(height*fabs(a)));
//		std::cout << Rangex << std::endl;
//		std::cout << Rangey << std::endl;
//		std::cout << img_rotate.cols<<" "<<img_rotate.rows<<std::endl;
//		std::cout << width_rotate << " " << height_rotate << std::endl;
//		img_rotate = img_rotate(Rangex, Rangey);
//	}
//	return img_rotate;
//}


int main(int argc, char *argv[],char**env)
{
	//int cubelength = 5;
	//int RowSideCount = 16;
	//int ColsSideCount = 32;
	//Mat CodeImage(2* RowSideCount*cubelength, ColsSideCount*cubelength,CV_8UC1, Scalar(0));
	//imshow("CodeImage1",CodeImage);


	//for (int i = 0; i < RowSideCount; i++)
	//{
	//	for (int rowOfCude = 0; rowOfCude < cubelength; rowOfCude++)
	//	{
	//		uchar * dataOfEachRow = CodeImage.ptr<uchar>(2*i*cubelength+ rowOfCude);
	//		for (int j = 0; j < ColsSideCount; j++)
	//		{
	//			uchar value;
	//			if (j % 2==1)
	//			{
	//				value = 128;
	//			}
	//			else
	//			{
	//				value = 0;
	//			}
	//			for (int k = 0; k < cubelength; k++)
	//			{
	//				dataOfEachRow[j*cubelength + k] = value;
	//			}
	//		}
	//	}
	//	for (int rowOfCude = 0; rowOfCude < cubelength; rowOfCude++)
	//	{
	//		uchar * dataOfEachRow = CodeImage.ptr<uchar>((2 * i+1)*cubelength + rowOfCude);
	//		for (int j = 0; j < ColsSideCount; j++)
	//		{
	//			uchar value;
	//			if (j % 2==1)
	//			{
	//				value = 255;
	//			}
	//			else
	//			{
	//				value = 125;
	//			}
	//			for (int k = 0; k < cubelength; k++)
	//			{
	//				dataOfEachRow[j*cubelength + k] = value;
	//			}
	//		}
	//	}
	//	//for(int i)
	//}
	//RotatedRect rRect = RotatedRect(Point2f(CodeImage.rows/2,CodeImage.cols/2), Size2f(pow(2, 0.5)*2*RowSideCount*cubelength / 2, pow(2,0.5)*ColsSideCount*cubelength/2), 45); //����һbai����ת����
	//Point2f vertices[4];
	//rRect.points(vertices);//��ȡ��ת���ε��ĸ��ǵ�du
	//for (int i = 0; i<4; i++)
	//{
	//	line(CodeImage, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0));//�ĸ��ǵ������ߣ������γ���ת�ľ��Ρ�
	//}

	//vector<bool> firstRow = { 1,1,0,0,1,0,0,1,1,0,1,0,0,0,1,1 };
	//vector<bool> secondRow = { 1,1,0,0,1,1,1,1,0,0,0,1,0,1,0,0 };
	//
	//for (int i = 0; i < firstRow.size(); i++)
	//{
	//	if (i % 2 == 0)
	//	{
	//		bool tem_value = firstRow[i];
	//		firstRow[i] = secondRow[i];
	//		secondRow[i] = tem_value;
	//	}
	//}

	//for (int i = RowSideCount - 1; i < 2 * RowSideCount; i++) //i-th row
	//{
	//	int inedx_colum = i - (RowSideCount - 1);  //the index of the row colored now
	//	int count = 0;   //the number of colored cube in each line
	//	int start_row = i;
	//	int start_col = i - (RowSideCount - 1);

	//	while(count<16)
	//	{
	//		int tem_value;

	//		if (inedx_colum % 2==0)
	//		{
	//			if (firstRow[count])
	//			{
	//				tem_value = - 75;
	//			}
	//			else
	//			{
	//				tem_value = 75;
	//			}
	//			
	//		}
	//		else
	//		{
	//			if (secondRow[count])
	//			{
	//				tem_value = -75;
	//			}
	//			else
	//			{
	//				tem_value = 75;
	//			}
	//		}
	//
	//		for (int k = 0; k < cubelength; k++)
	//		{
	//			uchar * DataOfEachRow = CodeImage.ptr<uchar>(start_row*cubelength+k);
	//			for (int num = start_col*cubelength; num < start_col*cubelength+cubelength; num++)
	//			{
	//				DataOfEachRow[num] += tem_value;
	//			}
	//		}

	//		start_row--;
	//		start_col++;
	//		count++;
	//	}
	//}

	//imshow("CodeImage2", CodeImage);

	////GaussianBlur(CodeImage, CodeImage, Size(5, 5), 10, 10);
	//blur(CodeImage, CodeImage, Size(5, 5));
	//imshow("CodeImage3", CodeImage);
	//CodeImage=rotateImage1(CodeImage, 45,0);
	//imshow("CodeImage4", CodeImage);
	//int Threshold = 150;
	//for (int i = 0; i < CodeImage.rows; i++)
	//{
	//	uchar * DataOfEachRow = CodeImage.ptr<uchar>(i);
	//	for (int j = 0; j < CodeImage.cols; j++)
	//	{
	//		if (DataOfEachRow[j] > Threshold)
	//		{
	//			DataOfEachRow[j] = 255;
	//		}
	//		else
	//		{
	//			DataOfEachRow[j] = 0;
	//		}
	//	}
	//}
	//imshow("CodeImage5", CodeImage);
	//int repeatrow = 12;
	//int repeatcol = 18;
	//Mat RepeatCodeImage(CodeImage.rows * repeatrow, CodeImage.cols * repeatcol, CV_8UC1, Scalar(0));
	//for (int i = 0; i < repeatrow; i++)
	//{
	//	for (int j = 0; j < repeatcol; j++)
	//	{
	//		for (int index_row = 0; index_row < CodeImage.rows; index_row++)
	//		{
	//			for (int index_col = 0; index_col < CodeImage.cols; index_col++)
	//			{
	//				RepeatCodeImage.at<uchar>(i*CodeImage.rows + index_row, j*CodeImage.cols + index_col) 
	//					= CodeImage.at<uchar>(index_row, index_col);
	//			}
	//		}
	//	}
	//}
	//imshow("CodeImage6", RepeatCodeImage);
	////RepeatCodeImage = rotateImage1(RepeatCodeImage, 10, 1);

	//imshow("CodeImage7", rotateImage1(RepeatCodeImage, 10, 1));
	//imshow("CodeImage8", rotateImage1(RepeatCodeImage, 10, 2));
	//waitKey();




	//std::cout << env[0][0] << env[0][1] << env[0][2] << env[0][3] << std::endl;

	//Mat M;
	//M.create(4, 4, CV_8UC(5));
	//cout << "M  " << M << endl;

	//std::vector<vector<int>> V1;
	//for (int j = 0; j < 5; j++)
	//{
	//	std::vector<int> V;
	//	for (int i = 0; i < 5; i++)
	//		V.push_back(i);
	//	V1.push_back(V);
	//}
	//Mat M2(V1);
	//cout << "M2 " << M2 << endl;
	//Mat sourceimage = imread("D:\\Toolkit\\OpenCV-4.3.0\\opencv\\sources\\samples\\data\\starry_night.jpg");
	//imshow("SourceImage", sourceimage);
	//Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	//Mat dstImage;
	//erode(sourceimage, dstImage, element);
	//Mat blur_image;
	//blur(sourceimage, blur_image, Size(5, 5));
	//Mat canny_dst_image, edge, grayImage;
	//canny_dst_image.create(sourceimage.size(), sourceimage.type());
	//cvtColor(sourceimage, grayImage, COLOR_BGR2GRAY);

	//blur(grayImage, edge, Size(3, 3));
	//Canny(edge, edge, 3, 9, 3);
	//imshow("desImage", dstImage);
	//imshow("blur_image", blur_image);
	//imshow("gray image", grayImage);
	//imshow("Canny image", edge);
	//waitKey(0);
	//return 0;
	//VideoCapture cap;
	//cap.open(0);
	//Mat edge;
	//if (!cap.isOpened())
	//{
	//	cout << "could not open the VideoCapture!" << endl;
	//	system("PAUSE");
	//	return -1;
	//}
	//const char * windowsname = "Example";
	//int k = -1;
	//namedWindow(windowsname);
	//int threshold1 = 0;
	//int threshold2 = 30;
	//int sizeOfSober = 3;
	//createTrackbar("threshold1", windowsname, &threshold1,100);
	//createTrackbar("threshold2", windowsname, &threshold2,100);
	//createTrackbar("sizeOfSober", windowsname, &sizeOfSober,10);
	//g_rectangle = Rect(-1, -1, 0, 0);

	//setMouseCallback(windowsname, On_MouseHandle);
	//while (true)
	//{
	//	Mat frame;
	//	bool ok = cap.read(frame);
	//	if (!ok)
	//	{
	//		break;
	//	}
	//	cvtColor(frame, edge, COLOR_BGR2GRAY);

	//	blur(edge, edge, Size(3, 3));

	//	Canny(edge, edge, threshold1, threshold2, sizeOfSober);
	//	cvtColor(edge, edge, COLOR_GRAY2BGR);
	//	if (g_bDrawingBox)
	//	{
	//		DrawRectangle(edge, g_rectangle,255,0,0);
	//	}
	//	for (int i=0;i<rectanglelist.size();i++)
	//	{
	//		//std::cout << rectanglelist[i].width << " " << rectanglelist[i].height << " " << rectanglelist[i].x << " " << rectanglelist[i].y << endl;
	//		std::cout << colorlist[i][0] <<"  "<< colorlist[i][1] <<"  "<< colorlist[i][2] << std::endl;
	//		DrawRectangle(edge, rectanglelist[i],colorlist[i][0],colorlist[i][1], colorlist[i][2]);
	//	}
	//	imshow(windowsname, edge);
	//	k = waitKey(33);
	//	if (k == 27) { break; }
	//}
	//waitKey(-1);
	//return 0;


	//��ʴ���Ͳ�������ʾ��

	////�ı�console������ɫ
	//system("color5E");

	////����ԭͼ
	//g_srcImage = imread("D:\\projects\\3DReconstruction\\MVCamera2\\WorkSpace\\WorkSpace3\\Reconstruction\\Leftimage32.png");
	//g_srcImage = imread("D:\\projects\\3DReconstruction\\MVCamera2\\bin\\Release\\997279a01fa16a797a070f4b7645895.jpg");
	//if (!g_srcImage.data) { printf("Oh��no����ȡsrcImage����~��\n"); return false; }

	////��ʾԭʼͼ
	//namedWindow("��ԭʼͼ��");
	//imshow("��ԭʼͼ��", g_srcImage);

	////���г��θ�ʴ��������ʾЧ��ͼ
	//namedWindow("��Ч��ͼ��");
	////��ȡ�Զ����
	//Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1), Point(g_nStructElementSize, g_nStructElementSize));
	//erode(g_srcImage, g_dstImage, element);
	//imshow("��Ч��ͼ��", g_dstImage);

	////�����켣��
	//createTrackbar("��ʴ/����", "��Ч��ͼ��", &g_nTrackbarNumer, 1, on_TrackbarNumChange);
	//createTrackbar("�ں˳ߴ�", "��Ч��ͼ��", &g_nStructElementSize, 21, on_ElementSizeChange);

	////���һЩ������Ϣ
	//cout << endl << "\t�š����гɹ���������������۲�ͼ��Ч��~\n\n"
	//	<< "\t���¡�q����ʱ�������˳�~!\n"
	//	<< "\n\n\t\t\t\tbyǳī";

	////��ѯ��ȡ������Ϣ������q���������˳�
	//while (char(waitKey(1)) != 'q') {}

	//return 0;

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();

}


//void Process()
//{
//	//��ȡ�Զ����
//	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1), Point(g_nStructElementSize, g_nStructElementSize));
//
//	//���и�ʴ�����Ͳ���
//	if (g_nTrackbarNumer == 0) {
//		erode(g_srcImage, g_dstImage, element);
//	}
//	else {
//		dilate(g_srcImage, g_dstImage, element);
//	}
//
//	//��ʾЧ��ͼ
//	imshow("��Ч��ͼ��", g_dstImage);
//}
//void on_TrackbarNumChange(int, void *)
//{
//	//��ʴ������֮��Ч���Ѿ��л����ص��������������һ��Process������ʹ�ı���Ч��������Ч����ʾ����
//	Process();
//}
//void on_ElementSizeChange(int, void *)
//{
//	//�ں˳ߴ��Ѹı䣬�ص��������������һ��Process������ʹ�ı���Ч��������Ч����ʾ����
//	Process();
//}

