#include "DotNetCoreHost.h"

#define LOCTEXT_NAMESPACE "FDotNetCoreHostModule"

void FDotNetCoreHostModule::StartupModule()
{
  wchar_t targetApp[MAX_PATH] = L"Test.dll";
  wchar_t targetAppPath[MAX_PATH] = L"C:/Temp/";

  CoreCLRModule = FPlatformProcess::GetDllHandle(L"C:\\Program Files\\dotnet\\shared\\Microsoft.NETCore.App\\2.0.0\\coreclr.dll");
  
  if (!CoreCLRModule)
  {
    UE_LOG(DotNetCoreHost, Error, TEXT("Unable load CoreCLR.dll."));

    return;
  }

  FnGetCLRRuntimeHost GetCLRRuntimeHost = (FnGetCLRRuntimeHost)FPlatformProcess::GetDllExport(CoreCLRModule, TEXT("GetCLRRuntimeHost"));

  if (!GetCLRRuntimeHost)
  {
    UE_LOG(DotNetCoreHost, Error, TEXT("Unable to find GetCLRRuntimeHost."));

    return;
  }

  if (FAILED(GetCLRRuntimeHost(IID_ICLRRuntimeHost2, (IUnknown**)&RuntimeHost)))
  {
    UE_LOG(DotNetCoreHost, Error, TEXT("Unable to access CLR runtime host interface."));

    return;
  }

  auto startupFlags =
    // Use concurrent GC
    STARTUP_FLAGS::STARTUP_CONCURRENT_GC |
    // All code executes in the default AppDomain (required to use the runtimeHost->ExecuteAssembly helper function)
    STARTUP_FLAGS::STARTUP_SINGLE_APPDOMAIN |
    // Prevents domain-neutral loading
    STARTUP_FLAGS::STARTUP_LOADER_OPTIMIZATION_SINGLE_DOMAIN;

  if (FAILED(RuntimeHost->SetStartupFlags(static_cast<STARTUP_FLAGS>(startupFlags))))
  {
    UE_LOG(DotNetCoreHost, Error, TEXT("Unable to set the CLR runtime start-up flags."));

    return;
  }

  if (FAILED(RuntimeHost->Start()))
  {
    UE_LOG(DotNetCoreHost, Error, TEXT("Unable to start the CLR runtime host."));

    return;
  }
}

void FDotNetCoreHostModule::ShutdownModule()
{
  if (RuntimeHost)
  {
    RuntimeHost->Release();
    RuntimeHost = nullptr;
  }

  if (CoreCLRModule)
  {
    FPlatformProcess::FreeDllHandle(CoreCLRModule);
    
    CoreCLRModule = nullptr;
  }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDotNetCoreHostModule, DotNetCoreHost)
DEFINE_LOG_CATEGORY(DotNetCoreHost);