#include "PluginAPI.h"
#include "Types.h"

extern "C" {

EXPORT int CALL RomOpen(void)
{
	return api().RomOpen();
}

EXPORT m64p_error CALL PluginGetVersion(
	m64p_plugin_type * _PluginType,
	int * _PluginVersion,
	int * _APIVersion,
	const char ** _PluginNamePtr,
	int * _Capabilities
)
{
	return api().PluginGetVersion(_PluginType, _PluginVersion, _APIVersion, _PluginNamePtr, _Capabilities);
}

} // extern "C"

// have to be outside extern "C" linkage
void(*MupenDebugCallback)(void *, int, const char *) = NULL;
void * MupenContext = NULL;

extern "C" {

EXPORT m64p_error CALL PluginStartup(
	m64p_dynlib_handle CoreLibHandle,
	void *Context,
	void (*DebugCallback)(void *, int, const char *)
)
{
	MupenContext = Context;
	MupenDebugCallback = DebugCallback;
	return api().PluginStartup(CoreLibHandle);
}

EXPORT m64p_error CALL PluginShutdown(void)
{
	return api().PluginShutdown();
}

EXPORT void CALL ReadScreen2(void *dest, int *width, int *height, int front)
{
	api().ReadScreen2(dest, width, height, front);
}

EXPORT void CALL SetRenderingCallback(void (*callback)(int))
{
	api().SetRenderingCallback(callback);
}

} // extern "C"
