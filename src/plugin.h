#ifndef plugin_h_
#define plugin_h_

#include "npapi.h"
#include "npfunctions.h"

#include "bugger.h"

#ifdef WIN32
    #define NP_EXPORT
#else
    #define NP_EXPORT _export
#endif

//Plugin instance data
typedef struct {
	NPP npp;
} PluginInstance;

#ifdef XP_MACOSX
NPError NP_Initialize(NPNetscapeFuncs *browserFuncs);
#else
NPError NP_Initialize(NPNetscapeFuncs* bFuncs, NPPluginFuncs* pFuncs);
#endif

NPError NP_GetEntryPoints(NPPluginFuncs *pluginFuncs);
NPError NP_Shutdown();

NPError NPP_New(NPMIMEType pluginType, NPP instance, uint16_t mode, int16_t argc, char* argn[], char* argv[], NPSavedData* saved);
NPError NPP_Destroy(NPP instance, NPSavedData** save);
NPError NPP_SetWindow(NPP instance, NPWindow* window);
NPError NPP_NewStream(NPP instance, NPMIMEType type, NPStream* stream, NPBool seekable, uint16_t* stype);
NPError NPP_DestroyStream(NPP instance, NPStream* stream, NPReason reason);
int32_t NPP_WriteReady(NPP instance, NPStream* stream);
int32_t NPP_Write(NPP instance, NPStream* stream, int32_t offset, int32_t len, void* buffer);
void    NPP_StreamAsFile(NPP instance, NPStream* stream, const char* fname);
void    NPP_Print(NPP instance, NPPrint* platformPrint);
int16_t NPP_HandleEvent(NPP instance, void* event);
void    NPP_URLNotify(NPP instance, const char* URL, NPReason reason, void* notifyData);
NPError NPP_GetValue(NPP instance, NPPVariable variable, void *value);
NPError NPP_SetValue(NPP instance, NPNVariable variable, void *value);

NPNetscapeFuncs *pNPNetscapeFuncs;

#define NPN_GetURL pNPNetscapeFuncs->geturl
#define NPN_PostURL pNPNetscapeFuncs->posturl
#define NPN_RequestRead pNPNetscapeFuncs->requestread
#define NPN_NewStream pNPNetscapeFuncs->newstream
#define NPN_Write pNPNetscapeFuncs->write
#define NPN_DestroyStream pNPNetscapeFuncs->destroystream
#define NPN_Status pNPNetscapeFuncs->status
#define NPN_UserAgent pNPNetscapeFuncs->uagent
#define NPN_MemAlloc pNPNetscapeFuncs->memalloc
#define NPN_MemFree pNPNetscapeFuncs->memfree
#define NPN_MemFlush pNPNetscapeFuncs->memflush
#define NPN_ReloadPlugins pNPNetscapeFuncs->reloadplugins
#define NPN_GetJavaEnv pNPNetscapeFuncs->getJavaEnv
#define NPN_GetJavaPeer pNPNetscapeFuncs->getJavaPeer
#define NPN_GetURLNotify pNPNetscapeFuncs->geturlnotify
#define NPN_PostURLNotify pNPNetscapeFuncs->posturlnotify
#define NPN_GetValue pNPNetscapeFuncs->getvalue
#define NPN_SetValue pNPNetscapeFuncs->setvalue
#define NPN_InvalidateRect pNPNetscapeFuncs->invalidaterect
#define NPN_InvalidateRegion pNPNetscapeFuncs->invalidateregion
#define NPN_ForceRedraw pNPNetscapeFuncs->forceredraw
#define NPN_GetStringIdentifier pNPNetscapeFuncs->getstringidentifier
#define NPN_GetStringIdentifiers pNPNetscapeFuncs->getstringidentifiers
#define NPN_GetIntIdentifier pNPNetscapeFuncs->getintidentifier
#define NPN_IdentifierIsString pNPNetscapeFuncs->identifierisstring
#define NPN_UTF8FromIdentifier pNPNetscapeFuncs->utf8fromidentifier
#define NPN_IntFromIdentifier pNPNetscapeFuncs->intfromidentifier
#define NPN_CreateObject pNPNetscapeFuncs->createobject
#define NPN_RetainObject pNPNetscapeFuncs->retainobject
#define NPN_ReleaseObject pNPNetscapeFuncs->releaseobject
#define NPN_Invoke pNPNetscapeFuncs->invoke
#define NPN_InvokeDefault pNPNetscapeFuncs->invokeDefault
#define NPN_Evaluate pNPNetscapeFuncs->evaluate
#define NPN_GetProperty pNPNetscapeFuncs->getproperty
#define NPN_SetProperty pNPNetscapeFuncs->setproperty
#define NPN_RemoveProperty pNPNetscapeFuncs->removeproperty
#define NPN_HasProperty pNPNetscapeFuncs->hasproperty
#define NPN_HasMethod pNPNetscapeFuncs->hasmethod
#define NPN_ReleaseVariantValue pNPNetscapeFuncs->releasevariantvalue
#define NPN_SetException pNPNetscapeFuncs->setexception
#define NPN_PushPopupsEnabledState pNPNetscapeFuncs->pushpopupsenabledstate
#define NPN_PopPopupsEnabledState pNPNetscapeFuncs->poppopupsenabledstate
#define NPN_Enumerate pNPNetscapeFuncs->enumerate
#define NPN_PluginThreadAsyncCall pNPNetscapeFuncs->pluginthreadasynccall
#define NPN_Construct pNPNetscapeFuncs->construct
#define NPN_GetValueForURL pNPNetscapeFuncs->getvalueforurl
#define NPN_SetValueForUR pNPNetscapeFuncs->setvalueforurl
#define NPN_GetAuthenticationInfoPtr pNPNetscapeFuncs->getauthenticationinfo
#define NPN_ScheduleTimerPtr pNPNetscapeFuncs->scheduletimer
#define NPN_UnscheduleTimerPtr pNPNetscapeFuncs->unscheduletimer
#define NPN_PopUpContextMenuPtr pNPNetscapeFuncs->popupcontextmenu
#define NPN_ConvertPointPtr pNPNetscapeFuncs->convertpoint
#define NPN_HandleEventPtr pNPNetscapeFuncs->handleevent
#define NPN_UnfocusInstancePtr pNPNetscapeFuncs->unfocusinstance
#define NPN_URLRedirectResponsePtr pNPNetscapeFuncs->urlredirectresponse

#endif // plugin_h_
