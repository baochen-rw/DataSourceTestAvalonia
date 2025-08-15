/*
 * @Author: JiangHannan
 * @Date: 2021-01-13 21:10:49
 * @LastEditTime: 2021-01-13 21:14:11
 * @LastEditors: JiangHannan
 * @Description: 
 * @FilePath: \xmld:\01.project\tmc-veleda\02.Tools\00.SourceCode\01.DataSourceUnitTestTool\DataSourceTestToolClient\Application\include\ts.h
 * @
 */
#ifndef TS_H
#define TS_H
// #define TSBASE_EXPORT (0)
// #define TSBASE_IMPORT (1)
#if defined(WIN32)
#pragma warning(disable: 4251 ) //disable export template stl 
#pragma warning(disable: 4244 ) //disable double to float 
#pragma warning(disable: 4800 )//disable convert into to bool 
#pragma warning(disable: 4005 )//disable macro redefined 
#endif
#if defined(TSBASE_EXPORT)
#define KANZIBASE_API __declspec(dllexport)
#elif defined(TSBASE_IMPORT)
#define KANZIBASE_API __declspec(dllimport)
#else
#define KANZIBASE_API 
#endif

#endif
