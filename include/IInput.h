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

#ifndef IINPUT_H
#define IINPUT_H

#include "KeyCode.h"
#include "MouseCode.h"
#include "VGUI2.h"
#include "interface.h"

namespace vgui2
{

class IInput : public IBaseInterface
{
public:
	virtual void SetMouseFocus( VPANEL newMouseFocus ) = 0;
	virtual void SetMouseCapture( VPANEL panel ) = 0;
	virtual void GetKeyCodeText( KeyCode code, char *buf, int buflen ) = 0;
	virtual VPANEL GetFocus() = 0;
	virtual VPANEL GetMouseOver() = 0;
	virtual void SetCursorPos( int x, int y ) = 0;
	virtual void GetCursorPos( int &x, int &y ) = 0;
	virtual bool WasMousePressed( MouseCode code ) = 0;
	virtual bool WasMouseDoublePressed( MouseCode code ) = 0;
	virtual bool IsMouseDown( MouseCode code ) = 0;
	virtual void SetCursorOveride( HCursor cursor ) = 0;
	virtual HCursor GetCursorOveride() = 0;
	virtual bool WasMouseReleased( MouseCode code ) = 0;
	virtual bool WasKeyPressed( KeyCode code ) = 0;
	virtual bool IsKeyDown( KeyCode code ) = 0;
	virtual bool WasKeyTyped( KeyCode code ) = 0;
	virtual bool WasKeyReleased( KeyCode code ) = 0;
	virtual VPANEL GetAppModalSurface() = 0;
	virtual void SetAppModalSurface( VPANEL panel ) = 0;
	virtual void ReleaseAppModalSurface() = 0;
	virtual void GetCursorPosition( int &x, int &y ) = 0;
};

#define VGUI_INPUT_INTERFACE_VERSION "VGUI_Input004"

} // namespace vgui2

#endif // IINPUT_H
