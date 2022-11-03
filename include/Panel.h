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

#ifndef PANEL_H
#define PANEL_H

#include "Color.h"
#include "IBorder.h"
#include "IClientPanel.h"
#include "KeyCode.h"
#include "MouseCode.h"

namespace vgui2
{

class Panel : public IClientPanel
{
public:
	Panel();
	Panel( Panel *parent );
	Panel( Panel *parent, const char *panelName );
	Panel( Panel *parent, const char *panelName, HScheme scheme );

	virtual ~Panel();

	virtual VPANEL GetVPanel();
	virtual void Think();
	virtual void PerformApplySchemeSettings();
	virtual void PaintTraverse( bool repaint, bool allowForce );
	virtual void Repaint();
	virtual VPANEL IsWithinTraverse( int x, int y, bool traversePopups );
	virtual void GetInset( int &left, int &top, int &right, int &bottom );
	virtual void GetClipRect( int &x0, int &y0, int &x1, int &y1 );
	virtual void OnChildAdded( VPANEL child );
	virtual void OnSizeChanged( int newWide, int newTall );
	virtual void InternalFocusChanged( bool lost );
	virtual bool RequestInfo( KeyValues *outputData );
	virtual void RequestFocus( int direction );
	virtual bool RequestFocusPrev( VPANEL panel );
	virtual bool RequestFocusNext( VPANEL panel );
	virtual void OnMessage( const KeyValues *params, VPANEL ifromPanel );
	virtual VPANEL GetCurrentKeyFocus();
	virtual int GetTabPosition();
	virtual const char *GetName();
	virtual const char *GetClassName();
	virtual HScheme GetScheme();
	virtual bool IsProportional();
	virtual bool IsAutoDeleteSet();
	virtual void DeletePanel();
	virtual void *QueryInterface( EInterfaceID id );
	virtual Panel *GetPanel();
	virtual const char *GetModuleName();

	virtual void OnCommand( const char *command );
	virtual void OnMouseCaptureLost();
	virtual void OnSetFocus();
	virtual void OnKillFocus();
	virtual void OnDelete();
	virtual void OnTick();
	virtual void OnCursorMoved( int x, int y );
	virtual void OnMouseFocusTicked();
	virtual void OnRequestFocus( VPANEL subFocus, VPANEL defaultPanel );
	virtual void InternalCursorMoved( int x, int y );
	virtual void InternalCursorEntered();
	virtual void InternalCursorExited();
	virtual void InternalMousePressed( MouseCode code );
	virtual void InternalMouseDoublePressed( MouseCode code );
	virtual void InternalMouseReleased( MouseCode code );
	virtual void InternalMouseWheeled( int delta );
	virtual void InternalKeyCodePressed( KeyCode code );
	virtual void InternalKeyCodeTyped( KeyCode code );
	virtual void InternalKeyTyped( int unichar );
	virtual void InternalKeyCodeReleased( KeyCode code );
	virtual void InternalKeyFocusTicked();
	virtual void InternalMouseFocusTicked();
	virtual void InternalInvalidateLayout();
	virtual void InternalMove();

	void Init( int x, int y, int wide, int tall );
	VPANEL GetVParent();
	void CallParentFunction( KeyValues *message );
	void InvalidateLayout( bool layoutNow = false, bool reloadScheme = false );
	int GetChildCount();
	Panel *GetChild( int index );
	void InternalPerformLayout();
	void PerformLayout();
	bool IsVisible();
	bool IsMouseInputEnabled();
	bool IsKeyBoardInputEnabled();
	bool IsWithin( int x, int y );
	void PaintBackground();
	void Paint();
	void PaintBorder();
	void PostChildPaint();
	void OnThink();
	void GetSize( int &wide, int &tall );
	Color GetBgColor();
	Color GetFgColor();
	void SetBgColor( Color _bgColor );
	void SetFgColor( Color _fgColor );
	void ApplySchemeSettings( IScheme *pScheme );
	Color GetSchemeColor( const char *keyName, IScheme *pScheme );
	void SetParent( Panel *parent );
	void SetScheme( HScheme _scheme );
	void SetName( const char *_name );
	void SetCursor( HCursor _cursor );
	HCursor GetCursor();
	bool IsCursorNone();
	void ScreenToLocal( int &x, int &y );
	void OnCursorEntered();
	void OnCursorExited();
	void OnMousePressed( MouseCode code );
	void OnMouseDoublePressed( MouseCode code );
	void OnMouseReleased( MouseCode code );
	void OnMouseWheeled( int delta );
	void OnKeyCodePressed( KeyCode code );
	void OnKeyCodeTyped( KeyCode code );
	void OnKeyTyped( int unichar );
	void OnKeyCodeReleased( KeyCode code );
	void OnKeyFocusTicked();
	void InternalSetCursor();
	void OnMove();
	bool HasParent( VPANEL potentialParent );
	void SetBounds( int x, int y, int wide, int tall );
	void SetPos( int x, int y );
	void SetSize( int wide, int tall );
	void SetPaintBorderEnabled( bool state );
	void SetPaintBackgroundEnabled( bool state );
	void SetPaintEnabled( bool state );
	void SetVisible( bool state );
	void SetZPos( int zpos );
	void SetScheme( const char *tag );

private:
	VPANEL vpanel;
	HScheme scheme;
	HCursor cursor;
	char *name;
	IBorder *border;
	int tabPosition;
	Color bgColor;
	Color fgColor;
	bool markedForDeletion;
	bool autoDelete;
	bool proportional;
	bool needsLayout;
	bool needsSchemeUpdate;
	bool needsRepaint;
	bool inPerformLayout;
	bool paintBackgroundEnabled;
	bool paintEnabled;
	bool paintBorderEnabled;
	bool postChildPaintEnabled;
};

} // namespace vgui2

#endif // PANEL_H
