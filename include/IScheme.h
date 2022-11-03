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

#ifndef ISCHEME_H
#define ISCHEME_H

#include "Color.h"
#include "VGUI2.h"
#include "interface.h"

namespace vgui2
{

class IBorder;
class IImage;

class IScheme : public IBaseInterface
{
public:
	virtual const char *GetResourceString( const char *stringName ) = 0;
	virtual IBorder *GetBorder( const char *borderName ) = 0;
	virtual HFont GetFont( const char *fontName, bool proportional ) = 0;
	virtual Color GetColor( const char *colorName, Color defaultColor ) = 0;
};

class ISchemeManager : public IBaseInterface
{
public:
	virtual HScheme LoadSchemeFromFile( const char *fileName, const char *tag ) = 0;
	virtual void ReloadSchemes() = 0;
	virtual HScheme GetDefaultScheme() = 0;
	virtual HScheme GetScheme( const char *tag ) = 0;
	virtual IImage *GetImage( const char *imageName, bool hardwareFiltered ) = 0;
	virtual HTexture GetImageID( const char *imageName, bool hardwareFiltered ) = 0;
	virtual class IScheme *GetIScheme( HScheme scheme ) = 0;
	virtual void Shutdown( bool full ) = 0;
	virtual int GetProportionalScaledValue( int normalizedValue ) = 0;
	virtual int GetProportionalNormalizedValue( int scaledValue ) = 0;
};

#define VGUI_SCHEME_INTERFACE_VERSION "VGUI_Scheme009"

}; // namespace vgui2

#endif // ISCHEME_H
