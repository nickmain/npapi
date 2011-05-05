//
//  scripting.h
//  test-npapi
//
//  Created by Nick Main on 5/1/11.
//  Copyright 2011. All rights reserved.
//

#ifndef scripting_h_
#define scripting_h_

#include "plugin.h"

//Script object data
typedef struct {
    NPObject npObject;
    PluginInstance* pluginInstance;
} PluginScriptObject;

//prototypical script object
typedef struct {
    PluginScriptObject scriptObject;
    //instance data goes here
} EmptyScriptObject;

//property descriptor
typedef struct {
    NPIdentifier name;
    NPGetPropertyFunctionPtr getter;
    NPSetPropertyFunctionPtr setter;
} PropertyDescriptor;

//method descriptor
typedef struct {
    NPIdentifier name;
} MethodDescriptor;

//class struct
typedef struct {
    NPClass npClass;
    long instanceSize;
    int propertyCount;
    int methodCount;
    PropertyDescriptor* properties;
    MethodDescriptor* methods;
} ScriptClass;

//get the NPP from an extended NPObject ptr
#define NPP_from_NPObject( pNPObject ) ((PluginScriptObject*) pNPObject)->pluginInstance->npp

//--NPClass functions
NPObject* NPAllocate(NPP npp, NPClass *aClass);
void NPDeallocate(NPObject *npobj);
void NPInvalidate(NPObject *npobj);
bool NPHasMethod(NPObject *npobj, NPIdentifier name);
bool NPInvoke(NPObject *npobj, NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
bool NPInvokeDefault(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result);
bool NPHasProperty(NPObject *npobj, NPIdentifier name);
bool NPGetProperty(NPObject *npobj, NPIdentifier name, NPVariant *result);
bool NPSetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value);
bool NPRemoveProperty(NPObject *npobj, NPIdentifier name);
bool NPEnumerate(NPObject *npobj, NPIdentifier **value, uint32_t *count);
bool NPConstruct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result);

void initializeClass( ScriptClass* pClass );

// copy a string to the result variant
void returnString( const NPUTF8* s, NPVariant* result );

#endif // scripting_h_
