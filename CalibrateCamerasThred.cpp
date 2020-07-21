#include<CalibrateCamerasThred.h>
CalibrateCamerasThred::CalibrateCamerasThred()
{

}

CalibrateCamerasThred::~CalibrateCamerasThred()
{
}

void CalibrateCamerasThred::run()
{
	Left_rvecsMat->clear();//ÿ��ͼ�����ת����
	Left_tvecsMat->clear();//ÿ��ͼ���ƽ������
	cv::calibrateCamera(*Left_object_points, *Left_Corner_buf, image_size, *Left_CameraMatrix, *Left_CameradistCoeffs, *Left_rvecsMat, *Left_tvecsMat, 0);//����궨


	std::cout << "camera left :" << std::endl << "camera matrix :" << *Left_CameraMatrix << std::endl;



	double total_err_Of_Camera1 = 0.0; /* ����ͼ���ƽ�������ܺ� */
	double err_Of_Camera1 = 0.0; /* ÿ��ͼ���ƽ����� */
	std::vector<cv::Point2f> Camera1_image_points2; /* �������¼���õ���ͶӰ�� */
	std::cout << "\tÿ��ͼ��ı궨��\n";
	for (int i = 0; i < Left_rvecsMat->size(); i++)
	{
		vector<Point3f> tempPointSet = Left_object_points->at(i);		/* ͨ���õ������������������Կռ����ά���������ͶӰ���㣬�õ��µ�ͶӰ�� */
		projectPoints(tempPointSet, Left_rvecsMat->at(i), Left_tvecsMat->at(i), *Left_CameraMatrix, *Left_CameradistCoeffs, Camera1_image_points2);		/* �����µ�ͶӰ��;ɵ�ͶӰ��֮������*/
		vector<Point2f> tempImagePoint = Left_Corner_buf->at(i);

		Mat image_points2Mat = Mat(1, Camera1_image_points2.size(), CV_32FC2);
		Mat tempImagePointMat = Mat(1, tempImagePoint.size(), CV_32FC2);
		for (int j = 0; j < tempImagePoint.size(); j++)
		{
			image_points2Mat.at<Vec2f>(0, j) = Vec2f(Camera1_image_points2[j].x, Camera1_image_points2[j].y);
			tempImagePointMat.at<Vec2f>(0, j) = Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);
		}

		err_Of_Camera1 = norm(image_points2Mat, tempImagePointMat, NORM_L2);
		err_Of_Camera1 /= board_size.height*board_size.width;
		total_err_Of_Camera1 += err_Of_Camera1;
		std::cout << "��" << i + 1 << "��ͼ���ƽ����" << err_Of_Camera1 << "����" << endl;
	}
	std::cout << "����ƽ����" << total_err_Of_Camera1 / Left_rvecsMat->size() << "����" << endl;
	Left_averageerror = total_err_Of_Camera1 / Left_rvecsMat->size();

	char cm1[100];
	std::sprintf(cm1, (WorkSpace + "\\calibrationParametersOfLeftCamera.txt").c_str());
	ofstream OutPut1(cm1);
	OutPut1 << "Camera Matrix: \n";
	std::cout << "Camera Matrix: \n";
	OutPut1 << *Left_CameraMatrix << std::endl;
	std::cout << *Left_CameraMatrix << std::endl;

	OutPut1 << "distortion Coeffs: \n";
	std::cout << "distortion Coeffs: \n";
	OutPut1 << *Left_CameradistCoeffs << std::endl;
	std::cout << *Left_CameradistCoeffs << std::endl;

	OutPut1 << "rvecsMatOfCamera: \n";
	OutPut1 << Left_rvecsMat->size() << std::endl;
	for (int i = 0; i < Left_rvecsMat->size(); i++)
	{
		OutPut1 << Left_rvecsMat->at(i) << std::endl;
	}
	OutPut1 << "tvecsMatOfCamera: \n";
	OutPut1 << Left_tvecsMat->size() << std::endl;
	for (int i = 0; i < Left_tvecsMat->size(); i++)
	{
		OutPut1 << Left_tvecsMat->at(i) << std::endl;
	}

	OutPut1.close();



	Right_rvecsMat->clear();//ÿ��ͼ�����ת����
	Right_tvecsMat->clear();//ÿ��ͼ���ƽ������
	cv::calibrateCamera(*Right_object_points, *Right_Corner_buf, image_size, *Right_CameraMatrix, *Right_CameradistCoeffs, *Right_rvecsMat, *Right_tvecsMat, 0);//����궨


	std::cout << "camera right :" << std::endl << "camera matrix :" << *Right_CameraMatrix << std::endl;



	total_err_Of_Camera1 = 0.0; /* ����ͼ���ƽ�������ܺ� */
	err_Of_Camera1 = 0.0; /* ÿ��ͼ���ƽ����� */
	Camera1_image_points2.clear(); /* �������¼���õ���ͶӰ�� */
	std::cout << "\tÿ��ͼ��ı궨��\n";
	for (int i = 0; i < Right_rvecsMat->size(); i++)
	{
		vector<Point3f> tempPointSet = Right_object_points->at(i);		/* ͨ���õ������������������Կռ����ά���������ͶӰ���㣬�õ��µ�ͶӰ�� */
		projectPoints(tempPointSet, Right_rvecsMat->at(i), Right_tvecsMat->at(i), *Right_CameraMatrix, *Right_CameradistCoeffs, Camera1_image_points2);		/* �����µ�ͶӰ��;ɵ�ͶӰ��֮������*/
		vector<Point2f> tempImagePoint = Right_Corner_buf->at(i);

		Mat image_points2Mat = Mat(1, Camera1_image_points2.size(), CV_32FC2);
		Mat tempImagePointMat = Mat(1, tempImagePoint.size(), CV_32FC2);
		for (int j = 0; j < tempImagePoint.size(); j++)
		{
			image_points2Mat.at<Vec2f>(0, j) = Vec2f(Camera1_image_points2[j].x, Camera1_image_points2[j].y);
			tempImagePointMat.at<Vec2f>(0, j) = Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);
		}

		err_Of_Camera1 = norm(image_points2Mat, tempImagePointMat, NORM_L2);
		err_Of_Camera1 /= board_size.height*board_size.width;
		total_err_Of_Camera1 += err_Of_Camera1;
		std::cout << "��" << i + 1 << "��ͼ���ƽ����" << err_Of_Camera1 << "����" << endl;
	}
	std::cout << "����ƽ����" << total_err_Of_Camera1 / Right_rvecsMat->size() << "����" << endl;
	Right_averageerror = total_err_Of_Camera1 / Right_rvecsMat->size();

	char cm2[100];
	std::sprintf(cm2, (WorkSpace + "\\calibrationParametersOfRightCamera.txt").c_str());
	ofstream OutPut2(cm2);
	OutPut2 << "Camera Matrix: \n";
	std::cout << "Camera Matrix: \n";
	OutPut2 << *Right_CameraMatrix << std::endl;
	std::cout << *Right_CameraMatrix << std::endl;

	OutPut2 << "distortion Coeffs: \n";
	std::cout << "distortion Coeffs: \n";
	OutPut2 << *Right_CameradistCoeffs << std::endl;
	std::cout << *Right_CameradistCoeffs << std::endl;

	OutPut2 << "rvecsMatOfCamera: \n";
	OutPut2 << Right_rvecsMat->size() << std::endl;
	for (int i = 0; i < Right_rvecsMat->size(); i++)
	{
		OutPut2 << Right_rvecsMat->at(i) << std::endl;
	}
	OutPut2 << "tvecsMatOfCamera: \n";
	OutPut2 << Right_tvecsMat->size() << std::endl;
	for (int i = 0; i < Right_tvecsMat->size(); i++)
	{
		OutPut2 << Right_tvecsMat->at(i) << std::endl;
	}
	OutPut2.close();

	//RenderPlaneAndCamera();
	emit FinishedCalibrate(Left_averageerror, Right_averageerror);
	quit();
}


//void CalibrateCamerasThred::TransformTV2TM(Mat rvecsMatOfCamera, Mat tvecsMatOfCamera, vtkSmartPointer<vtkMatrix4x4> RTM)
//{
//	//double R_matrix[9];
//	//CvMat pr_vec = rvecsMatOfCamera;
//	//CvMat pR_matrix;
//	//cvInitMatHeader(&pR_matrix, 3, 3, CV_64FC1, R_matrix, CV_AUTOSTEP);
//
//	//cvRodrigues2(&pr_vec, &pR_matrix, 0);//����ת��������ת����
//	Mat outputArray;
//	Rodrigues(rvecsMatOfCamera, outputArray);
//	//std::cout << "output array"<<outputArray<<std::endl;
//	//string ty = cv::typeToString(outputArray.type());
//	//printf("Matrix: %s %dx%d \n", ty.c_str(), outputArray.cols, outputArray.rows);
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			//std::cout << outputArray.at<double>(i, j)<<" ";
//			RTM->SetElement(i, j, outputArray.at<double>(i, j));
//		}
//	}
//	//for (int i = 0; i < 3; i++)
//	//{
//	//	for (int j = 0; j < 3; j++)
//	//	{
//	//		RTM->SetElement(i, j, cvmGet(&pR_matrix, i, j));
//	//	}
//	//}
//
//	for (int i = 0; i < 3; i++)
//	{
//		RTM->SetElement(i, 3, tvecsMatOfCamera.at<double>(i));
//		RTM->SetElement(3, i, 0);
//	}
//
//	RTM->SetElement(3, 3, 1);
//
//}