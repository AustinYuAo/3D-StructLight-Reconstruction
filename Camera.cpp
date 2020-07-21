#include "Camera.h"
Camera::Camera(QObject  *parent) : QObject(parent)

{
	
	// ���������̵߳�ʵ��û��ֱ�ӵĹ�ϵ����������ʵʵ�������Լ�������
	hmv = NULL;
	detectChessBoard = false;
	ifundistort = false;
	wheatherCapturePicture = false;
	wheatherCapturePicture2 = false;
	iftracking = false;
	iftracking2 = false;
	ifreconstruction = false;
	ifreconstruction2 = false;
	imageSavePath = "./";
	IMGCOUNT = 0;
	Name = "Camera";
	cameraMatrix = Mat(3, 3, CV_64FC1, Scalar::all(0));//������ڲ������� 
	distCoeffs= Mat(1, 5, CV_64FC1, Scalar::all(0));//�������5������ϵ����k1,k2,p1,p2,k3


	board_size = Size(4,6);
}


//Camera::Camera()
//{
//	hmv = NULL;
//}
//
//Camera::~Camera()
//{
//}

Mat Camera::ImageCapture()
{
	//tSdkCameraCapbility sCameraInfo;
	tSdkFrameHead imgFrInfo;		//���ڱ��浱ǰͼ��֡��֡ͷ��Ϣ
	BYTE *imgBuffer;        //����ԭʼͼ�����ݵĻ�����

	CameraGetImageBuffer(hmv, &imgFrInfo, &imgBuffer, 1000);	//ԭʼ���ݶ���Bayer��ʽ��
	BYTE *m_imgBuffer = new BYTE[imgFrInfo.iWidth*imgFrInfo.iHeight * 3];//����RGB���ݵĻ�����
	CameraImageProcess(hmv, imgBuffer, m_imgBuffer, &imgFrInfo);	//����õ�ԭʼ����ת����RGB��ʽ������
	Mat res(imgFrInfo.iHeight, imgFrInfo.iWidth, CV_8UC3);		//ͼ���С��֪
	memcpy(res.ptr(0), m_imgBuffer, imgFrInfo.iWidth*imgFrInfo.iHeight * 3);//���Ƶ�Mat����res��
	CameraReleaseImageBuffer(hmv, imgBuffer);//�ͷŻ���
	delete[]m_imgBuffer;
	m_imgBuffer = NULL;
	return res;
}

void Camera::myCreate(int AEC, int Gain)// ����HMV��ʼ����loc��Ϣ��ʼ�����
{
	double Time;
	bool mode = false; //TRUE��ʹ���Զ��ع⣻FALSE��ֹͣ�Զ��ع⡣
					   //�����ع�ģʽ
	CameraSetAeState(hmv, mode);
	//�ع�ʱ��
	CameraSetExposureTime(hmv, AEC);
	//��������
	CameraSetGain(hmv, Gain, Gain, Gain);
	//�鿴�ع�ʱ��
	CameraGetExposureTime(hmv, &Time);
	////����Ƶ��
	//CameraSetFrameSpeed(hmv, 1);
	//���ڷֱ���
	//tSdkImageResolution *Resolution = {};
	//CameraSetResolutionForSnap(hmv, Resolution);


}

void Camera::CamInit(tSdkCameraDevInfo sCameraList)
{

	//��ʼ�������(-1,-1)��ʾ�����ϴ��˳�ǰ����Ĳ���������ǵ�һ��ʹ�ø�����������Ĭ�ϲ���.
	if ((CameraInit(&sCameraList, -1, -1, &hmv)) != CAMERA_STATUS_SUCCESS)
	{
		printf("Failed to init the camera!\n");
	}

	//tSdkCameraCapbility *Capbility;

	//CameraGetCapability(hmv, Capbility);

	//std::cout << Capbility->iFrameSpeedDesc << endl;
	//�Զ��庯���Զ����������
	myCreate(30000.0, 500);

	//�����ʼ�ɼ�ͼ��
	CameraPlay(hmv);
}

void Camera::RenderPicture()
{	
	CorresponedChessBoard.clear();
	//std::cout << this->Name << std::endl;
	Mat mat,mat1,mat2;
	int flag=0; //��̬ͨ
	mat = ImageCapture();
	cvtColor(mat, mat, COLOR_RGB2GRAY);
	if(ifundistort)
	{
		undistort(mat, mat1,this->cameraMatrix,this->distCoeffs);
	}
	else
	{
		mat.copyTo(mat1);
	}
	
	cv::resize(mat1, mat1, Size(mat1.cols / 4, mat1.rows / 4));
	cv::flip(mat1, mat1, 0);


	mat1.copyTo(mat2);
	if (this->detectChessBoard)
	{
		
		//Mat img1;
		vector<Point2f> image_points_buf1;//����ÿ��ͼ���ϼ�⵽�Ľǵ�
		bool findcorner1 = findChessboardCorners(mat1, board_size, image_points_buf1);
		//cvtColor(mat1, img1, CV_RGB2GRAY);
		if (!findcorner1)
		{
			//cout << "can not find chessboard corners in cmaera 2 !\n"; //�Ҳ����ǵ�  
			flag = 2; //δ�ɹ�������̸�̬												   /*return;*/
		}
		else
		{
			/*�����ؾ�ȷ��*/
			cornerSubPix(mat1, image_points_buf1, Size(5, 5), Size(-1, -1), TermCriteria(1+ 2, 30, 0.1));
			//find4QuadCornerSubpix(img2, image_points_buf_2, Size(5, 5)); //�Դ���ȡ�Ľǵ���о�ȷ��  
			flag = 1;//�ɹ�������̸�̬

		}

	

		if (findcorner1)
		{
			drawChessboardCorners(mat2, board_size, image_points_buf1, true); //������ͼƬ�б�ǽǵ�
			if (wheatherCapturePicture || iftracking)
			{
				for (int index = 0; index < image_points_buf1.size(); index++)
				{
					//std::cout << "Write" << std::endl;
					CorresponedChessBoard.push_back(image_points_buf1[index]);
				}
			}
			if (wheatherCapturePicture)
			{

				//WriteCapturedImage();
				CapturedImage = mat1;

				
				
			}
			
			
		}
		

	}

	if (this->ifreconstruction)
	{
		CapturedImage = mat1;
	}



	//cvtColor(mat2, mat2, COLOR_BGR2RGB);

	//imshow("window", mat2);
	//waitKey(30);
	//QImage disImage1 = QImage((const unsigned char*)(mat2.data), mat2.cols, mat2.rows, QImage::Format_RGB888);
	QImage disImage1 = QImage((const unsigned char*)(mat2.data), mat2.cols, mat2.rows, QImage::Format_Grayscale8);
	//QGraphicsScene *scene1 = new QGraphicsScene;//ͼ����ʾ        
	//scene1->addPixmap(QPixmap::fromImage(disImage1));        
	//ui->graphicsView_Left->setScene(scene1);        
	//ui->graphicsView_Left->show();

	Label->setPixmap(QPixmap::fromImage(disImage1.scaled(Label->size(), Qt::KeepAspectRatio)));
	if (wheatherCapturePicture)
	{
		wheatherCapturePicture2 = true;
	}
	if (iftracking)
	{
		iftracking2 = true;
	}
	if (ifreconstruction)
	{
		ifreconstruction2 = true;
	}
	emit wheatherSuccessCapturePicture(flag);

}

//void Camera::CapturePicture(bool flag)
//{
//	wheatherCapturePicture = flag;
//
//}
//void Camera::SetTracking(bool tracking)
//{
//	iftracking = tracking;
//}
void Camera::WriteCapturedImage()
{

	char s1[100], sc1[100];
	sprintf(s1, (imageSavePath + "\\" + Name + "Image%d.png").c_str(), IMGCOUNT);

	imwrite(s1, CapturedImage);

	sprintf(sc1, (imageSavePath + "\\" + Name + "ChessBoard%d.txt").c_str(), IMGCOUNT);
	ofstream OutPut1(sc1);

	std::cout << CorresponedChessBoard.size() << std::endl;

	for (int index = 0; index < CorresponedChessBoard.size(); index++)
	{
		OutPut1 << CorresponedChessBoard.at(index).x << "," << CorresponedChessBoard.at(index).y << std::endl;
		//std::cout << "WRITE " << Name << std::endl;
	}
	OutPut1.close();
	CorresponedChessBoard.clear();
}
void Camera::GetChessBoard(vector<Point2f>& chessboard)
{
	chessboard.clear();
	for (int i = 0; i < CorresponedChessBoard.size(); i++)
	{
		chessboard.push_back(CorresponedChessBoard[i]);
}
}

