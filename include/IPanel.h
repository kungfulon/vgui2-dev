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

#ifndef IPANEL_H
#define IPANEL_H

#include "VGUI2.h"
#include "interface.h"

#ifdef SendMessage
#undef SendMessage
#endif

class KeyValues;

namespace vgui2
{

class SurfacePlat;
class IClientPanel;
class Panel;

class IPanel : public IBaseInterface
{
public:
	virtual void Init( VPANEL vguiPanel, IClientPanel *panel ) = 0;
	virtual void SetPos( VPANEL vguiPanel, int x, int y ) = 0;
	virtual void GetPos( VPANEL vguiPanel, int &x, int &y ) = 0;
	virtual void SetSize( VPANEL vguiPanel, int wide, int tall ) = 0;
	virtual void GetSize( VPANEL vguiPanel, int &wide, int &tall ) = 0;
	virtual void SetMinimumSize( VPANEL vguiPanel, int wide, int tall ) = 0;
	virtual void GetMinimumSize( VPANEL vguiPanel, int &wide, int &tall ) = 0;
	virtual void SetZPos( VPANEL vguiPanel, int z ) = 0;
	virtual int GetZPos( VPANEL vguiPanel ) = 0;
	virtual void GetAbsPos( VPANEL vguiPanel, int &x, int &y ) = 0;
	virtual void GetClipRect( VPANEL vguiPanel, int &x0, int &y0, int &x1, int &y1 ) = 0;
	virtual void SetInset( VPANEL vguiPanel, int left, int top, int right, int bottom ) = 0;
	virtual void GetInset( VPANEL vguiPanel, int &left, int &top, int &right, int &bottom ) = 0;
	virtual void SetVisible( VPANEL vguiPanel, bool state ) = 0;
	virtual bool IsVisible( VPANEL vguiPanel ) = 0;
	virtual void SetParent( VPANEL vguiPanel, VPANEL newParent ) = 0;
	virtual int GetChildCount( VPANEL vguiPanel ) = 0;
	virtual VPANEL GetChild( VPANEL vguiPanel, int index ) = 0;
	virtual VPANEL GetParent( VPANEL vguiPanel ) = 0;
	virtual void MoveToFront( VPANEL vguiPanel ) = 0;
	virtual void MoveToBack( VPANEL vguiPanel ) = 0;
	virtual bool HasParent( VPANEL vguiPanel, VPANEL potentialParent ) = 0;
	virtual bool IsPopup( VPANEL vguiPanel ) = 0;
	virtual void SetPopup( VPANEL vguiPanel, bool state ) = 0;
	virtual bool Render_GetPopupVisible( VPANEL vguiPanel ) = 0;
	virtual void Render_SetPopupVisible( VPANEL vguiPanel, bool state ) = 0;
	virtual HScheme GetScheme( VPANEL vguiPanel ) = 0;
	virtual bool IsProportional( VPANEL vguiPanel ) = 0;
	virtual bool IsAutoDeleteSet( VPANEL vguiPanel ) = 0;
	virtual void DeletePanel( VPANEL vguiPanel ) = 0;
	virtual void SetKeyBoardInputEnabled( VPANEL vguiPanel, bool state ) = 0;
	virtual void SetMouseInputEnabled( VPANEL vguiPanel, bool state ) = 0;
	virtual bool IsKeyBoardInputEnabled( VPANEL vguiPanel ) = 0;
	virtual bool IsMouseInputEnabled( VPANEL vguiPanel ) = 0;
	virtual void Solve( VPANEL vguiPanel ) = 0;
	virtual const char *GetName( VPANEL vguiPanel ) = 0;
	virtual const char *GetClassName( VPANEL vguiPanel ) = 0;
	virtual void SendMessage( VPANEL vguiPanel, KeyValues *params, VPANEL ifromPanel ) = 0;
	virtual void Think( VPANEL vguiPanel ) = 0;
	virtual void PerformApplySchemeSettings( VPANEL vguiPanel ) = 0;
	virtual void PaintTraverse( VPANEL vguiPanel, bool forceRepaint, bool allowForce ) = 0;
	virtual void Repaint( VPANEL vguiPanel ) = 0;
	virtual VPANEL IsWithinTraverse( VPANEL vguiPanel, int x, int y, bool traversePopups ) = 0;
	virtual void OnChildAdded( VPANEL vguiPanel, VPANEL child ) = 0;
	virtual void OnSizeChanged( VPANEL vguiPanel, int newWide, int newTall ) = 0;
	virtual void InternalFocusChanged( VPANEL vguiPanel, bool lost ) = 0;
	virtual bool RequestInfo( VPANEL vguiPanel, KeyValues *outputData ) = 0;
	virtual void RequestFocus( VPANEL vguiPanel, int direction ) = 0;
	virtual bool RequestFocusPrev( VPANEL vguiPanel, VPANEL existingPanel ) = 0;
	virtual bool RequestFocusNext( VPANEL vguiPanel, VPANEL existingPanel ) = 0;
	virtual VPANEL GetCurrentKeyFocus( VPANEL vguiPanel ) = 0;
	virtual int GetTabPosition( VPANEL vguiPanel ) = 0;
	virtual SurfacePlat *Plat( VPANEL vguiPanel ) = 0;
	virtual void SetPlat( VPANEL vguiPanel, SurfacePlat *Plat ) = 0;
	virtual Panel *GetPanel( VPANEL vguiPanel, const char *destinationModule ) = 0;
	virtual bool IsEnabled( VPANEL vguiPanel ) = 0;
	virtual void SetEnabled( VPANEL vguiPanel, bool state ) = 0;
};

#define VGUI_PANEL_INTERFACE_VERSION "VGUI_Panel007"

} // namespace vgui2

#endif // IPANEL_H
