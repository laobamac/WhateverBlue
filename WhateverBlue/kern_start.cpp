//
//  kern_start.cpp
//  WhateverBlue
//
//  Copyright © 2017 vit9696. All rights reserved.
//

#include <Headers/plugin_start.hpp>
#include <Headers/kern_api.hpp>

#include "kern_web.hpp"

static WEB web;

static const char *bootargOff[] {
	"-weboff"
};

static const char *bootargDebug[] {
	"-webdbg"
};

static const char *bootargBeta[] {
	"-webbeta"
};

PluginConfiguration ADDPR(config) {
	xStringify(PRODUCT_NAME),
	parseModuleVersion(xStringify(MODULE_VERSION)),
	LiluAPI::AllowNormal | LiluAPI::AllowInstallerRecovery | LiluAPI::AllowSafeMode,
	bootargOff,
	arrsize(bootargOff),
	bootargDebug,
	arrsize(bootargDebug),
	bootargBeta,
	arrsize(bootargBeta),
	KernelVersion::SnowLeopard,
	KernelVersion::Sequoia,
	[]() {
		web.init();
	}
};
