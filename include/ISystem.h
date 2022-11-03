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

#ifndef ISYSTEM_H
#define ISYSTEM_H

#include "KeyCode.h"
#include "interface.h"

class KeyValues;

namespace vgui2
{

class ISystem : public IBaseInterface
{
public:
	virtual void Shutdown() = 0;
	virtual void RunFrame() = 0;
	virtual void ShellExecute( const char *command, const char *file ) = 0;
	virtual double GetFrameTime() = 0;
	virtual double GetCurrentTime() = 0;
	virtual long int GetTimeMillis() = 0;
	virtual int GetClipboardTextCount() = 0;
	virtual void SetClipboardText( const char *text, int textLen ) = 0;
	virtual void SetClipboardText( const wchar_t *text, int textLen ) = 0;
	virtual int GetClipboardText( int offset, char *buf, int bufLen ) = 0;
	virtual int GetClipboardText( int offset, wchar_t *buf, int bufLen ) = 0;
	virtual bool SetRegistryString( const char *key, const char *value ) = 0;
	virtual bool GetRegistryString( const char *key, char *value, int valueLen ) = 0;
	virtual bool SetRegistryInteger( const char *key, int value ) = 0;
	virtual bool GetRegistryInteger( const char *key, int &value ) = 0;
	virtual KeyValues *GetUserConfigFileData( const char *dialogName, int dialogID ) = 0;
	virtual void SetUserConfigFile( const char *fileName, const char *pathName ) = 0;
	virtual void SaveUserConfigFile() = 0;
	virtual bool SetWatchForComputerUse( bool state ) = 0;
	virtual double GetTimeSinceLastUse() = 0;
	virtual int GetAvailableDrives( char *buf, int bufLen ) = 0;
	virtual bool CommandLineParamExists( const char *paramName ) = 0;
	virtual const char *GetFullCommandLine() = 0;
	virtual bool GetCurrentTimeAndDate( int *year, int *month, int *dayOfWeek, int *day, int *hour, int *minute, int *second ) = 0;
	virtual double GetFreeDiskSpace( const char *path ) = 0;
	virtual bool CreateShortcut( const char *linkFileName, const char *targetPath, const char *arguments, const char *workingDirectory, const char *iconFile ) = 0;
	virtual bool GetShortcutTarget( const char *linkFileName, char *targetPath, char *arguments, int destBufferSizes ) = 0;
	virtual bool ModifyShortcutTarget( const char *linkFileName, const char *targetPath, const char *arguments, const char *workingDirectory ) = 0;
	virtual bool GetCommandLineParamValue( const char *paramName, char *value, int valueBufferSize ) = 0;
	virtual bool DeleteRegistryKey( const char *keyName ) = 0;
	virtual const char *GetDesktopFolderPath() = 0;
	virtual KeyCode KeyCode_VirtualKeyToVGUI( int keyCode ) = 0;
	virtual int KeyCode_VGUIToVirtualKey( KeyCode keyCode ) = 0;
};

#define VGUI_SYSTEM_INTERFACE_VERSION "VGUI_System009"

} // namespace vgui2

#endif // ISYSTEM_H
