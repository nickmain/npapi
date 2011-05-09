//
//  scripting.c
//  test-npapi
//
//  Created by Nick Main on 5/1/11.
//  Copyright 2011. All rights reserved.
//

#include "scripting.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


NPObject* NPAllocate(NPP npp, NPClass *aClass) {
    ScriptClass* scriptClass = (ScriptClass*) aClass;
    
	int instanceSize = scriptClass->instanceSize;

	PluginScriptObject* pObj = malloc(instanceSize);
    memset( pObj, 0, instanceSize );
    pObj->npObject._class = aClass;
    pObj->pluginInstance = npp->pdata;

    DEBUGI( "allocated", pObj )
    return (NPObject*) pObj;
}

void NPDeallocate(NPObject *npobj) {
	DEBUGI("NPDeallocate", npobj)
    free(npobj);
}

void NPInvalidate(NPObject *npobj) {
    //nada
}

bool NPHasMethod(NPObject *npobj, NPIdentifier name) {
    ScriptClass* pClass = (ScriptClass*) npobj->_class;

    int methCount = pClass->methodCount;
    MethodDescriptor* meths = pClass->methods;
    for( int i = 0; i < methCount; i++ ) {
        if( meths[i].name == name ) return true;
    }
    
	return false;
}

bool NPInvoke(NPObject *npobj, NPIdentifier name, const NPVariant *args,
              uint32_t argCount, NPVariant *result) {
	return false;
}

bool NPInvokeDefault(NPObject *npobj, const NPVariant *args, uint32_t argCount,
                     NPVariant *result) {
	return false;
}

bool NPHasProperty(NPObject *npobj, NPIdentifier name) {
    ScriptClass* pClass = (ScriptClass*) npobj->_class;
    
    int propCount = pClass->propertyCount;
    PropertyDescriptor* props = pClass->properties;
    for( int i = 0; i < propCount; i++ ) {
        if( props[i].name == name ) return true;
    }
    
	return false;
}

bool NPGetProperty(NPObject *npobj, NPIdentifier name, NPVariant *result) {
    ScriptClass* pClass = (ScriptClass*) npobj->_class;
    
    int propCount = pClass->propertyCount;
    PropertyDescriptor* props = pClass->properties;
    for( int i = 0; i < propCount; i++ ) {
        if( props[i].name == name ) {
            return props[i].getter( npobj, name, result );
        }
    }
    
    return false;
}

bool NPSetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value) {
	return false;
}

bool NPRemoveProperty(NPObject *npobj, NPIdentifier name) {
	return false;
}

bool NPEnumerate(NPObject *npobj, NPIdentifier **value, uint32_t *count) {
	return false;
}

bool NPConstruct(NPObject *npobj, const NPVariant *args, uint32_t argCount,
                 NPVariant *result) {
	DEBUG( "NPConstruct" )
	return false;
}

void initializeClass( ScriptClass* pScriptClass ) {
    NPClass* pClass = (NPClass*) pScriptClass;
    pClass->structVersion  = NP_CLASS_STRUCT_VERSION;
    pClass->allocate       = NPAllocate;
    pClass->deallocate     = NPDeallocate;
    pClass->invalidate     = NPInvalidate;
    pClass->hasMethod      = NPHasMethod;
    pClass->invoke         = NPInvoke;
    pClass->invokeDefault  = NPInvokeDefault;
    pClass->hasProperty    = NPHasProperty;
    pClass->getProperty    = NPGetProperty;
    pClass->setProperty    = NPSetProperty;
    pClass->removeProperty = NPRemoveProperty;
    pClass->enumerate      = NPEnumerate;
    pClass->construct      = NPConstruct;
}
