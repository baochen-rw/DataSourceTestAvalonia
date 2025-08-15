/*
 * @Author: JiangHannan
 * @Date: 2021-01-13 20:04:05
 * @LastEditTime: 2021-05-15 03:58:52
 * @LastEditors: JiangHannan
 * @Description:
 * @FilePath: \src\TestToolApplication.h
 * @
 */
#pragma once

#include <kanzi/kanzi.hpp>

class TestToolApplication : public kanzi::Application
{
public:
	// Configures application.
	virtual void onConfigure(kanzi::ApplicationProperties &configuration) KZ_OVERRIDE;

	// Initializes application after project has been loaded.
	virtual void onProjectLoaded() KZ_OVERRIDE;

	virtual void registerMetadataOverride(kanzi::ObjectFactory & /*factory*/) KZ_OVERRIDE;

	virtual void onKeyInputEvent(const KzsInputEventKey *inputData) KZ_OVERRIDE;

	~TestToolApplication();
};
