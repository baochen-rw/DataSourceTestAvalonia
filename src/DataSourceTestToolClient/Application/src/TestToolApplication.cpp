/*
 * @Author: JiangHannan
 * @Date: 2021-01-13 20:04:05
 * @LastEditTime: 2021-05-15 03:59:00
 * @LastEditors: JiangHannan
 * @Description:
 * @FilePath: \src\TestToolApplication.cpp
 * @
 */
#include "TestToolApplication.h"
// TODO: Add missing header files
// #include "clusterdatasourcemodule.h"
// #include "labelenhanced_module.hpp"
// #include "modeldata.h"
// #include "clusterdataupdate.h"
// #include "mapplugin_module.hpp"
// #include "texthelper_module.hpp"
// #include "prefabview_module.hpp"
// #include "gmeter_module.hpp"
#include "TestToolClient.h"
// #include "warning_module.hpp"
using namespace kanzi;

// Configures application.
void TestToolApplication::onConfigure(kanzi::ApplicationProperties &configuration)
{
	configuration.performanceInfoLevel = kanzi::ApplicationProperties::PerformanceInfoLevelFPS;
}

// Initializes application after project has been loaded.
void TestToolApplication::onProjectLoaded()
{
	// Code to run after the .KZB has been loaded.
	TestToolClient::getInstance().connectTools(this, getDomain());
}

void TestToolApplication::registerMetadataOverride(kanzi::ObjectFactory & /*factory*/)
{
	// TODO: Re-enable module registrations when header files are available
	// KanziComponentsModule::registerModule(getDomain());
	// ClusterDataSourceModule::registerModule(getDomain());
	// MapPluginModule::registerModule(getDomain());
	// LabelEnhancedModule::registerModule(getDomain());
	// TextHelperModule::registerModule(getDomain());
	// PrefabViewModule::registerModule(getDomain());
	// WarningModule::registerModule(getDomain());
	// getDomain()->registerModule<GMeterModule>("G_Meter");
}

void TestToolApplication::onKeyInputEvent(const KzsInputEventKey *inputData)
{
	KzsInputKey button = kzsInputEventKeyGetButton(inputData);

	if (button == KZS_KEY_ESC || button == KZS_KEY_Q || button == KZS_KEY_BACKSPACE)
	{
		quit();
	}
}

TestToolApplication::~TestToolApplication()
{
	TestToolClient::getInstance().~TestToolClient();
}
