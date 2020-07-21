#ifndef CAMERA_H
#define CAMERA_H

#include <Windows.h>	// ���ͷ�ļ�����Ҫ
#include "../Camera/CameraApi.h"
//#include "../Camera/CameraApiLoad.h"
#include "../Camera/CameraDefine.h"
#include "../Camera/CameraStatus.h"
#pragma comment(lib,"../lib/MVCAMSDK_X64.lib")//Ԥ����

#include<qobject.h>
// opencv
#include <opencv2\opencv.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <qlabel.h>
#include <qthread.h>

typedef unsigned char BYTE;
using namespace cv;
using namespace std;

class Camera : public QObject
{
	Q_OBJECT

public:
	explicit  Camera(QObject * parent=0);
	//Camera();
	//~Camera();

	// ��ҵ�����ʼ��
	Mat ImageCapture();			    // �������HMV����ȡһ��ͼ��
	void myCreate(int AEC, int Gain);// ����HMV��ʼ����loc��Ϣ��ʼ�����
	void CamInit(tSdkCameraDevInfo sCameraList); // ����idx,range��ʼ�����
	void WriteCapturedImage();
	void SetTracking(bool );
	void GetChessBoard(vector<Point2f> &);
	//void CapturePicture(bool);

	Mat CapturedImage;
	vector<Point2f> CorresponedChessBoard;
	bool detectChessBoard;
	Size board_size;
	std::string imageSavePath;
	int IMGCOUNT;
	std::string Name;
	Mat cameraMatrix;
	Mat distCoeffs;

	bool ifundistort;

	bool wheatherCapturePicture;
	bool wheatherCapturePicture2;

	bool iftracking;
	bool iftracking2;


	bool ifreconstruction;
	bool ifreconstruction2;
signals:
	void wheatherSuccessCapturePicture(int);


public slots:
	void RenderPicture();



private:
	CameraHandle hmv;
	QLabel * Label;





};
#endif
