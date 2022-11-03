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

#ifndef ICLIENTPANEL_H
#define ICLIENTPANEL_H

#include "VGUI2.h"

#ifdef GetClassName
#undef GetClassName
#endif

class KeyValues;

namespace vgui2
{

class Panel;

enum EInterfaceID
{
	ICLIENTPANEL_STANDARD_INTERFACE = 0,
};

class IClientPanel
{
public:
	virtual VPANEL GetVPanel() = 0;
	virtual void Think() = 0;
	virtual void PerformApplySchemeSettings() = 0;
	virtual void PaintTraverse( bool repaint, bool allowForce ) = 0;
	virtual void Repaint() = 0;
	virtual VPANEL IsWithinTraverse( int x, int y, bool traversePopups ) = 0;
	virtual void GetInset( int &left, int &top, int &right, int &bottom ) = 0;
	virtual void GetClipRect( int &x0, int &y0, int &x1, int &y1 ) = 0;
	virtual void OnChildAdded( VPANEL child ) = 0;
	virtual void OnSizeChanged( int newWide, int newTall ) = 0;
	virtual void InternalFocusChanged( bool lost ) = 0;
	virtual bool RequestInfo( KeyValues *outputData ) = 0;
	virtual void RequestFocus( int direction ) = 0;
	virtual bool RequestFocusPrev( VPANEL panel ) = 0;
	virtual bool RequestFocusNext( VPANEL panel ) = 0;
	virtual void OnMessage( const KeyValues *params, VPANEL ifromPanel ) = 0;
	virtual VPANEL GetCurrentKeyFocus() = 0;
	virtual int GetTabPosition() = 0;
	virtual const char *GetName() = 0;
	virtual const char *GetClassName() = 0;
	virtual HScheme GetScheme() = 0;
	virtual bool IsProportional() = 0;
	virtual bool IsAutoDeleteSet() = 0;
	virtual void DeletePanel() = 0;
	virtual void *QueryInterface( EInterfaceID id ) = 0;
	virtual Panel *GetPanel() = 0;
	virtual const char *GetModuleName() = 0;
};

} // namespace vgui2

#endif // ICLIENTPANEL_H
