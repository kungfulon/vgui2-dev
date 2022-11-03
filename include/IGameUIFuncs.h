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

#ifndef IGAMEUIFUNCS_H
#define IGAMEUIFUNCS_H

#include "KeyCode.h"
#include "interface.h"
#include "modes.h"

class IGameUIFuncs : public IBaseInterface
{
public:
	virtual bool IsKeyDown( const char *keyname, bool &isdown ) = 0;
	virtual const char *Key_NameForKey( int keynum ) = 0;
	virtual const char *Key_BindingForKey( int keynum ) = 0;
	virtual vgui2::KeyCode GetVGUI2KeyCodeForBind( const char *bind ) = 0;
	virtual void GetVideoModes( vmode_t **liststart, int *count ) = 0;
	virtual void GetCurrentVideoMode( int *wide, int *tall, int *bpp ) = 0;
	virtual void GetCurrentRenderer( char *name, int namelen, int *windowed, int *hdmodels, int *addons_folder, int *vid_level ) = 0;
	virtual bool IsConnectedToVACSecureServer() = 0;
	virtual int Key_KeyStringToKeyNum( const char *pchKey ) = 0;
};

#define VENGINE_GAMEUIFUNCS_VERSION "VENGINE_GAMEUIFUNCS_VERSION001"

#endif // IGAMEUIFUNCS_H
