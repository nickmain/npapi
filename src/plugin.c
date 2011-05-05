#include "plugin.h"
#include "scripting.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PLUGIN_NAME        "Basic Test Plug-in"
#define PLUGIN_DESCRIPTION "Test Plug-in"
#define PLUGIN_VERSION     "1.0.0.3"

static NPNetscapeFuncs* pNPNetscapeFuncs = NULL;

static ScriptClass pluginClass;
static PropertyDescriptor props[2];

static bool GetFoo(NPObject *npobj, NPIdentifier name, NPVariant *result) {
    returnString( "Hello from Foo !", result );

	return true;
}

static bool GetBar(NPObject *npobj, NPIdentifier name, NPVariant *result) {
	NPObject* pWindow;
	NPP instance = NPP_from_NPObject(npobj);
	if( NPN_GetValue(instance,NPNVWindowNPObject,&pWindow) == NPERR_NO_ERROR ) {
		returnString( "SUCCESS", result );

		NPVariant docResult;
		NPIdentifier idDocument = NPN_GetStringIdentifier("document");
		NPIdentifier idTitle    = NPN_GetStringIdentifier("title");

		if( NPN_GetProperty(instance, pWindow, idDocument, &docResult ) ){
			NPVariant titleResult;

			NPObject* pDoc = NPVARIANT_TO_OBJECT(docResult);

			if( NPN_GetProperty(instance, pDoc, idTitle, &titleResult ) ){
				returnString( NPVARIANT_TO_STRING(titleResult).UTF8Characters, result );
				NPN_ReleaseVariantValue(&titleResult);
			}

			NPN_ReleaseVariantValue(&docResult);
		}

		NPN_ReleaseObject(pWindow);
		return true;
	}
	else {
		returnString( "FAILED", result );
		return true;
	}
}


#ifdef XP_MACOSX
NPError NP_Initialize(NPNetscapeFuncs* bFuncs) {
#else
NPError NP_Initialize(NPNetscapeFuncs* bFuncs, NPPluginFuncs* pFuncs) {
#endif
	
    pNPNetscapeFuncs = bFuncs;
    
    initializeClass( &pluginClass );
    pluginClass.instanceSize = sizeof(EmptyScriptObject);
    pluginClass.methodCount = 0;
    pluginClass.propertyCount = 2;
    pluginClass.methods = NULL;
    pluginClass.properties = props;
    
    props[0].name = NPN_GetStringIdentifier("foo");
    props[0].getter = GetFoo;
    props[1].name = NPN_GetStringIdentifier("bar");
    props[1].getter = GetBar;
    
    //TODO dealloc for class
    
    
    
#ifdef XP_MACOSX
	return NPERR_NO_ERROR;
#else
    return NP_GetEntryPoints(pFuncs);
#endif
}    
    
NPError NP_GetEntryPoints(NPPluginFuncs *pFuncs) {
    
	pFuncs->newp = NPP_New;
	pFuncs->destroy = NPP_Destroy;
	pFuncs->setwindow = NPP_SetWindow;
	pFuncs->newstream = NPP_NewStream;
	pFuncs->destroystream = NPP_DestroyStream;
	pFuncs->asfile = NPP_StreamAsFile;
	pFuncs->writeready = NPP_WriteReady;
	pFuncs->write = NPP_Write;
	pFuncs->print = NPP_Print;
	pFuncs->event = NPP_HandleEvent;
	pFuncs->urlnotify = NPP_URLNotify;
	pFuncs->getvalue = NPP_GetValue;
	pFuncs->setvalue = NPP_SetValue;

	return NPERR_NO_ERROR;
}

char* NP_GetPluginVersion() {
	return PLUGIN_VERSION;
}

char* NP_GetMIMEDescription() {
	return "application/test-plugin:test:Test plugin";
}

NPError NP_GetValue(void* future, NPPVariable aVariable, void* aValue) {

	switch (aVariable) {
	case NPPVpluginNameString:
		*((char**) aValue) = PLUGIN_NAME;
		break;
	case NPPVpluginDescriptionString:
		*((char**) aValue) = PLUGIN_DESCRIPTION;
		break;
		//case NPPVpluginScriptableNPObject:

	default:
		return NPERR_INVALID_PARAM;
		break;
	}
	return NPERR_NO_ERROR;
}

NPError NP_Shutdown() {
	return NPERR_NO_ERROR;
}

NPError NPP_New(NPMIMEType pluginType, NPP instance, uint16_t mode,
		int16_t argc, char* argn[], char* argv[], NPSavedData* saved) {

	PluginInstance* instanceData = (PluginInstance*) malloc(sizeof(PluginInstance));
	if (!instanceData)
		return NPERR_OUT_OF_MEMORY_ERROR;

	memset(instanceData, 0, sizeof(PluginInstance));
	instanceData->npp = instance;
	instance->pdata = instanceData;

	return NPERR_NO_ERROR;
}

NPError NPP_Destroy(NPP instance, NPSavedData** save) {
	PluginInstance* instanceData = (PluginInstance*) (instance->pdata);

	free(instanceData);
	return NPERR_NO_ERROR;
}

NPError NPP_GetValue(NPP instance, NPPVariable variable, void *value) {
	switch (variable) {
	case NPPVpluginScriptableNPObject: {
		*((NPObject**) value) = NPN_CreateObject(instance, &pluginClass.npClass);
		break;
	}

	case NPPVpluginNeedsXEmbed:
		*((bool*) value) = true;
		break;

	default:
		return NPERR_INVALID_PARAM;
		break;
	}

	return NPERR_NO_ERROR;
}


//================ Unimplemented NPP functions ========================    
    
NPError NPP_SetWindow(NPP instance, NPWindow* window) {
	return NPERR_NO_ERROR;
}

NPError NPP_NewStream(NPP instance, NPMIMEType type, NPStream* stream,
		NPBool seekable, uint16_t* stype) {
	return NPERR_GENERIC_ERROR;
}

NPError NPP_DestroyStream(NPP instance, NPStream* stream, NPReason reason) {
	return NPERR_GENERIC_ERROR;
}

int32_t NPP_WriteReady(NPP instance, NPStream* stream) {
	return 0;
}

int32_t NPP_Write(NPP instance, NPStream* stream, int32_t offset, int32_t len,
		void* buffer) {
	return 0;
}

void NPP_StreamAsFile(NPP instance, NPStream* stream, const char* fname) {
}

void NPP_Print(NPP instance, NPPrint* platformPrint) {
}

int16_t NPP_HandleEvent(NPP instance, void* event) {
	return false;
}

void NPP_URLNotify(NPP instance, const char* URL, NPReason reason,
		void* notifyData) {
}

NPError NPP_SetValue(NPP instance, NPNVariable variable, void *value) {
	return NPERR_GENERIC_ERROR;
}

