/*
 * @Author: JiangHannan
 * @Date: 2021-05-15 03:51:03
 * @LastEditTime: 2021-05-15 03:57:19
 * @LastEditors: JiangHannan
 * @Description:
 * @FilePath: \src\Main.cpp
 *
 */

#include "TestToolApplication.h"
#include "TestToolClient.h"

kanzi::Application *createApplication()
{
#ifdef __linux__
	// TestToolClient::getKzbFile();
#endif //__linux__
	return new TestToolApplication;
}
