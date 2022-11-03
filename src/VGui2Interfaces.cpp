/*
Copyright (C) 2022 Bien Pham

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

In addition, as a special exception, the author gives permission
to link the code of this program with VGUI library developed by
Valve, L.L.C ("Valve"). You must obey the GNU General Public License
in all respects for all of the code used other than VGUI library.
If you modify this file, you may extend this exception to your
version of the file, but you are not obligated to do so. If
you do not wish to do so, delete this exception statement
from your version.

*/

#include "VGui2Interfaces.h"
#include "KeyValues.h"
#include <locale.h>
#include <string.h>

static IKeyValues *keyValuesInterface;

IKeyValues *keyvalues()
{
	return keyValuesInterface;
}

namespace vgui2
{

static IVGui *vguiInterface;

IVGui *ivgui()
{
	return vguiInterface;
}

static ILocalize *localizeInterface;

ILocalize *localize()
{
	return localizeInterface;
}

static IFileSystem *fileSystemInterface;

IFileSystem *filesystem()
{
	return fileSystemInterface;
}

static IPanel *panelInterface;

IPanel *ipanel()
{
	return panelInterface;
}

static ISurface *surfaceInterface;

ISurface *surface()
{
	return surfaceInterface;
}

static ISchemeManager *schemeManagerInterface;

ISchemeManager *scheme()
{
	return schemeManagerInterface;
}

static ISystem *systemInterface;

ISystem *system()
{
	return systemInterface;
}

static IInput *inputInterface;

IInput *input()
{
	return inputInterface;
}

static IInputInternal *inputInternalInterface;

IInputInternal *inputinternal()
{
	return inputInternalInterface;
}

static char moduleName[256];

bool InitializeVGui2Interfaces( const char *_moduleName, CreateInterfaceFn *factories, int factoryCount )
{
	strncpy( moduleName, _moduleName, sizeof( moduleName ) );
	moduleName[sizeof( moduleName ) - 1] = '\0';

	setlocale( LC_ALL, "" );
	setlocale( LC_CTYPE, "" );
	setlocale( LC_MONETARY, "" );
	setlocale( LC_NUMERIC, "" );

	if ( factoryCount <= 0 )
	{
		keyValuesInterface = nullptr;
		vguiInterface = nullptr;
		localizeInterface = nullptr;
		fileSystemInterface = nullptr;
		panelInterface = nullptr;
		surfaceInterface = nullptr;
		schemeManagerInterface = nullptr;
		systemInterface = nullptr;
		inputInterface = nullptr;
		inputInternalInterface = nullptr;

		return false;
	}

	for ( int i = 0; i < factoryCount; ++i )
	{
		if ( keyValuesInterface == nullptr )
			keyValuesInterface = (IKeyValues *)factories[i]( KEYVALUES_INTERFACE_VERSION, nullptr );

		if ( vguiInterface == nullptr )
			vguiInterface = (IVGui *)factories[i]( VGUI_IVGUI_INTERFACE_VERSION, nullptr );

		if ( localizeInterface == nullptr )
			localizeInterface = (ILocalize *)factories[i]( VGUI_LOCALIZE_INTERFACE_VERSION, nullptr );

		if ( fileSystemInterface == nullptr )
			fileSystemInterface = (IFileSystem *)factories[i]( "VFileSystem009", nullptr );

		if ( panelInterface == nullptr )
			panelInterface = (IPanel *)factories[i]( VGUI_PANEL_INTERFACE_VERSION, nullptr );

		if ( surfaceInterface == nullptr )
			surfaceInterface = (ISurface *)factories[i]( VGUI_SURFACE_INTERFACE_VERSION, nullptr );

		if ( schemeManagerInterface == nullptr )
			schemeManagerInterface = (ISchemeManager *)factories[i]( VGUI_SCHEME_INTERFACE_VERSION, nullptr );

		if ( systemInterface == nullptr )
			systemInterface = (ISystem *)factories[i]( VGUI_SYSTEM_INTERFACE_VERSION, nullptr );

		if ( inputInterface == nullptr )
			inputInterface = (IInput *)factories[i]( VGUI_INPUT_INTERFACE_VERSION, nullptr );

		if ( inputInternalInterface == nullptr )
			inputInternalInterface = (IInputInternal *)factories[i]( VGUI_INPUTINTERNAL_INTERFACE_VERSION, nullptr );
	}

	if ( keyValuesInterface == nullptr ||
		 vguiInterface == nullptr ||
		 localizeInterface == nullptr ||
		 fileSystemInterface == nullptr ||
		 panelInterface == nullptr ||
		 surfaceInterface == nullptr ||
		 schemeManagerInterface == nullptr ||
		 systemInterface == nullptr ||
		 inputInterface == nullptr ||
		 inputInternalInterface == nullptr )
		return false;

	vguiInterface->Init( factories, factoryCount );
	keyValuesInterface->RegisterSizeofKeyValues( sizeof( KeyValues ) );

	return true;
}

const char *GetModuleName()
{
	return moduleName;
}

} // namespace vgui2
