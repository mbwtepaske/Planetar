#pragma once

#include "MessageLog.h"
#include "ModuleManager.h"

#include "mscoree.h"

DECLARE_LOG_CATEGORY_EXTERN(DotNetCoreHost, Log, All);

class FDotNetCoreHostModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
  LPVOID            CoreCLRModule;
  ICLRRuntimeHost2*	RuntimeHost;
};