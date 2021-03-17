/*
* Copyright (c) 2017-2020 CelePixel Technology Co. Ltd. All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <opencv2/opencv.hpp>
#include <celex5/celex5.h>

#ifdef _WIN32
#include <windows.h>
#include<process.h>
#else
#include<unistd.h>
#include <signal.h>
#include<pthread.h>
#endif

#define FPN_PATH    "../Samples/config/FPN_2.txt"
#define BIN_FILE    "/home/yuguanfeng/MipiData_20210302_150548827_FO1_100M.bin"

CeleX5 *pCeleX5 = new CeleX5;

#ifdef _WIN32
bool exit_handler(DWORD fdwctrltype)
{
	switch (fdwctrltype)
	{
		//ctrl-close: confirm that the user wants to exit.
	case CTRL_CLOSE_EVENT:
	case CTRL_C_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		delete pCeleX5;
		pCeleX5 = NULL;
		return(true);
	default:
		return false;
		}
	}
#else
void exit_handler(int sig_num)
{
	printf("SIGNAL received: num =%d\n", sig_num);
	if (sig_num == 1 || sig_num == 2 || sig_num == 3 || sig_num == 9 || sig_num == 15)
	{
		delete pCeleX5;
		pCeleX5 = NULL;
		exit(0);
	}
}
#endif

int main()
{
	if (pCeleX5 == NULL)
		return 0;
    //pCeleX5->openSensor(CeleX5::CeleX5_MIPI);
	if(!pCeleX5->openBinFile(BIN_FILE))
    {
        std::cout << "Can not open bin file！" << std::endl;
        return 0;
    }
    CeleX5::CeleX5Mode sensorMode = (CeleX5::CeleX5Mode)pCeleX5->getBinFileAttributes().loopAMode;
	//pCeleX5->setSensorFixedMode(sensorMode);

#ifdef _WIN32
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)exit_handler, true);
#else
	// install signal use sigaction
	struct sigaction sig_action;
	sigemptyset(&sig_action.sa_mask);
	sig_action.sa_flags = 0;
	sig_action.sa_handler = exit_handler;
	sigaction(SIGHUP, &sig_action, NULL);  // 1
	sigaction(SIGINT, &sig_action, NULL);  // 2
	sigaction(SIGQUIT, &sig_action, NULL); // 3
	sigaction(SIGKILL, &sig_action, NULL); // 9
	sigaction(SIGTERM, &sig_action, NULL); // 15
#endif

	uint8_t* pImageBuffer = new uint8_t[CELEX5_PIXELS_NUMBER];

	while (true)
	{
        if(pCeleX5)
        {
            pCeleX5->readBinFileData();//start reading the bin file
        }

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

#ifdef _WIN32
		Sleep(1);
#else
		usleep(1000);
#endif
	}
	return 1;
}
