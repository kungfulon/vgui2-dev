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

#ifndef ILOCALIZE_H
#define ILOCALIZE_H

#include "interface.h"

class KeyValues;
class IFileSystem;

namespace vgui2
{

typedef unsigned long StringIndex_t;

class ILocalize : public IBaseInterface
{
public:
	virtual bool AddFile( IFileSystem *fileSystem, const char *szFileName ) = 0;
	virtual void RemoveAll() = 0;
	virtual wchar_t *Find( const char *pName ) = 0;
	virtual int ConvertANSIToUnicode( const char *ansi, wchar_t *unicode, int unicodeBufferSizeInBytes ) = 0;
	virtual int ConvertUnicodeToANSI( const wchar_t *unicode, char *ansi, int ansiBufferSize ) = 0;
	virtual StringIndex_t FindIndex( const char *pName ) = 0;
	virtual void ConstructString( wchar_t *unicodeOutput, int unicodeBufferSizeInBytes, wchar_t *formatString, int numFormatParameters, ... ) = 0;
	virtual const char *GetNameByIndex( StringIndex_t index ) = 0;
	virtual wchar_t *GetValueByIndex( StringIndex_t index ) = 0;
	virtual StringIndex_t GetFirstStringIndex() = 0;
	virtual StringIndex_t GetNextStringIndex( StringIndex_t index ) = 0;
	virtual void AddString( const char *pString, wchar_t *pValue, const char *fileName ) = 0;
	virtual void SetValueByIndex( StringIndex_t index, wchar_t *newValue ) = 0;
	virtual bool SaveToFile( IFileSystem *fileSystem, const char *szFileName ) = 0;
	virtual int GetLocalizationFileCount() = 0;
	virtual const char *GetLocalizationFileName( int index ) = 0;
	virtual const char *GetFileNameByIndex( StringIndex_t index ) = 0;
	virtual void ReloadLocalizationFiles( IFileSystem *filesystem ) = 0;
	virtual void ConstructString( wchar_t *unicodeOutput, int unicodeBufferSizeInBytes, const char *tokenName, KeyValues *localizationVariables ) = 0;
	virtual void ConstructString( wchar_t *unicodeOutput, int unicodeBufferSizeInBytes, vgui2::StringIndex_t unlocalizedTextSymbol, KeyValues *localizationVariables ) = 0;
};

#define VGUI_LOCALIZE_INTERFACE_VERSION "VGUI_Localize003"

} // namespace vgui2

#endif // ILOCALIZE_H
