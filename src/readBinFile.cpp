#include <opencv2/opencv.hpp>
#include <celex5/celex5.h>
#include <celex5/celex5datamanager.h>
#include <celex5/celex5processeddata.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define FPN_PATH "../cfg/FPN_2.txt"
#define BIN_FILE "/home/yuguanfeng/MipiData_20210302_150548827_FO1_100M.bin"

CeleX5 *pCeleX5 = new CeleX5;

class SensorDataObserver : public CeleX5DataManager
{
public:
	SensorDataObserver(CX5SensorDataServer* pServer)
	{
		m_pServer = pServer;
		m_pServer->registerData(this, CeleX5DataManager::CeleX_Frame_Data);
	}
	~SensorDataObserver()
	{
		m_pServer->unregisterData(this, CeleX5DataManager::CeleX_Frame_Data);
	}
	virtual void onFrameDataUpdated(CeleX5ProcessedData* pSensorData);//overrides Observer operation
	CX5SensorDataServer* m_pServer;
};

uint8_t * pImageBuffer = new uint8_t[CELEX5_PIXELS_NUMBER];

void SensorDataObserver::onFrameDataUpdated(CeleX5ProcessedData* pSensorData)
{
	if (NULL == pSensorData)
		return;

	CeleX5::CeleX5Mode sensorMode = pSensorData->getSensorMode();

	if (CeleX5::Full_Picture_Mode == sensorMode)
	{
		//full-frame picture
		pCeleX5->getFullPicBuffer(pImageBuffer);
		cv::Mat matFullPic(800, 1280, CV_8UC1, pImageBuffer);
		cv::imshow("FullPic", matFullPic);
		cv::waitKey(1);
	}
	else if (CeleX5::Event_Off_Pixel_Timestamp_Mode == sensorMode)
	{
		//get buffers when sensor works in EventMode
		pCeleX5->getEventPicBuffer(pImageBuffer, CeleX5::EventBinaryPic);
		cv::Mat matEventPic(800, 1280, CV_8UC1, pImageBuffer);
		cv::imshow("Event Binary Pic", matEventPic);
		cvWaitKey(1);
	}
	else if (CeleX5::Optical_Flow_Mode == sensorMode)
	{
		//full-frame optical-flow pic
		pCeleX5->getOpticalFlowPicBuffer(pImageBuffer, CeleX5::OpticalFlowPic);
		cv::Mat matOpticalFlow(800, 1280, CV_8UC1, pImageBuffer);
		cv::imshow("Optical-Flow Pic", matOpticalFlow);
		cvWaitKey(1);
	}
}


int main()
{
	if (pCeleX5 == NULL)
		return 0;
	//pCeleX5->openSensor(CeleX5::CeleX5_MIPI);
	bool success = pCeleX5->openBinFile(BIN_FILE);	//open the bin file
	CeleX5::CeleX5Mode sensorMode = (CeleX5::CeleX5Mode)pCeleX5->getBinFileAttributes().loopAMode;

	SensorDataObserver* pSensorData = new SensorDataObserver(pCeleX5->getSensorDataServer());

	while (true)
	{
		if (pCeleX5)
		{
			pCeleX5->readBinFileData();	//start reading the bin file
		}
#ifdef _WIN32
		Sleep(1);
#else
		usleep(1000);
#endif
	}
	return 1;
}


