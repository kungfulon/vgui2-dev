#include "Panel.h"
#include "Cursor.h"
#include "KeyValues.h"
#include "VGui2Interfaces.h"
#include <string.h>

namespace vgui2
{

Panel::Panel()
{
	Init( 0, 0, 64, 24 );
}

Panel::Panel( Panel *parent )
{
	Init( 0, 0, 64, 24 );
	SetParent( parent );
}

Panel::Panel( Panel *parent, const char *panelName )
{
	Init( 0, 0, 64, 24 );
	SetName( panelName );
	SetParent( parent );
}

Panel::Panel( Panel *parent, const char *panelName, HScheme scheme )
{
	Init( 0, 0, 64, 24 );
	SetName( panelName );
	SetParent( parent );
	SetScheme( scheme );
}

Panel::~Panel()
{
	markedForDeletion = true;
	autoDelete = false;
	SetParent( NULL );

	while ( ipanel()->GetChildCount( vpanel ) > 0 )
	{
		VPANEL child = ipanel()->GetChild( vpanel, 0 );
		if ( ipanel()->IsAutoDeleteSet( child ) )
			ipanel()->DeletePanel( child );
		else
			ipanel()->SetParent( child, NULL );
	}

	if ( name != nullptr )
	{
		delete[] name;
		name = nullptr;
	}

	ivgui()->FreePanel( vpanel );
	vpanel = NULL;
}

void Panel::Init( int x, int y, int wide, int tall )
{
	vpanel = ivgui()->AllocPanel();
	ipanel()->Init( vpanel, this );
	ipanel()->SetPos( vpanel, x, y );
	ipanel()->SetSize( vpanel, wide, tall );

	scheme = NULL;
	cursor = dc_arrow;
	name = nullptr;
	border = nullptr;
	tabPosition = 0;
	markedForDeletion = false;
	autoDelete = true;
	proportional = false;
	needsLayout = true;
	needsSchemeUpdate = true;
	needsRepaint = false;
	inPerformLayout = false;
	paintBackgroundEnabled = true;
	paintEnabled = true;
	paintBorderEnabled = true;
	postChildPaintEnabled = false;
}

VPANEL Panel::GetVPanel()
{
	return vpanel;
}

void Panel::Think()
{
	if ( IsVisible() )
	{
		if ( needsLayout )
			InternalPerformLayout();
	}

	OnThink();
}

void Panel::PerformApplySchemeSettings()
{
	if ( !needsSchemeUpdate )
		return;

	IScheme *pScheme = vgui2::scheme()->GetIScheme( GetScheme() );
	if ( pScheme != nullptr )
		ApplySchemeSettings( pScheme );
}

void Panel::PaintTraverse( bool repaint, bool allowForce )
{
	if ( !IsVisible() )
		return;

	if ( !repaint && allowForce && needsRepaint )
	{
		repaint = true;
		needsRepaint = false;
	}

	VPANEL vpanel = GetVPanel();

	int clipRect[4];
	ipanel()->GetClipRect( vpanel, clipRect[0], clipRect[1], clipRect[2], clipRect[3] );
	if ( ( clipRect[2] <= clipRect[0] ) || ( clipRect[3] <= clipRect[1] ) )
		repaint = false;

	if ( repaint )
	{
		if ( paintBackgroundEnabled )
		{
			surface()->PushMakeCurrent( vpanel, false );
			PaintBackground();
			surface()->PopMakeCurrent( vpanel );
		}

		if ( paintEnabled )
		{
			surface()->PushMakeCurrent( vpanel, true );
			Paint();
			surface()->PopMakeCurrent( vpanel );
		}
	}

	for ( int i = 0; i < GetChildCount(); i++ )
	{
		VPANEL child = ipanel()->GetChild( GetVPanel(), i );
		bool bVisible = ipanel()->IsVisible( child );

		if ( surface()->ShouldPaintChildPanel( child ) )
		{
			if ( bVisible )
				ipanel()->PaintTraverse( child, repaint, allowForce );
		}
		else
		{
			surface()->Invalidate( child );

			if ( bVisible )
				ipanel()->PaintTraverse( child, false, false );
		}
	}

	if ( repaint )
	{
		if ( paintBorderEnabled && border != nullptr )
		{
			surface()->PushMakeCurrent( vpanel, false );
			PaintBorder();
			surface()->PopMakeCurrent( vpanel );
		}

		if ( postChildPaintEnabled )
		{
			surface()->PushMakeCurrent( vpanel, false );
			PostChildPaint();
			surface()->PopMakeCurrent( vpanel );
		}
	}

	surface()->SwapBuffers( vpanel );
}

void Panel::Repaint()
{
	needsRepaint = true;
	surface()->Invalidate( GetVPanel() );
}

VPANEL Panel::IsWithinTraverse( int x, int y, bool traversePopups )
{
	if ( !IsVisible() || !IsMouseInputEnabled() )
		return NULL;

	if ( traversePopups )
	{
		for ( int i = GetChildCount() - 1; i >= 0; i-- )
		{
			VPANEL panel = ipanel()->GetChild( GetVPanel(), i );
			if ( !ipanel()->IsPopup( panel ) )
				continue;

			panel = ipanel()->IsWithinTraverse( panel, x, y, true );
			if ( panel )
				return panel;
		}

		for ( int i = GetChildCount() - 1; i >= 0; i-- )
		{
			VPANEL panel = ipanel()->GetChild( GetVPanel(), i );
			if ( ipanel()->IsPopup( panel ) )
				continue;

			panel = ipanel()->IsWithinTraverse( panel, x, y, true );
			if ( panel )
				return panel;
		}

		if ( IsWithin( x, y ) )
			return GetVPanel();
	}
	else
	{
		if ( IsWithin( x, y ) )
		{
			for ( int i = GetChildCount() - 1; i >= 0; i-- )
			{
				VPANEL panel = ipanel()->GetChild( GetVPanel(), i );
				if ( ipanel()->IsPopup( panel ) )
					continue;

				panel = ipanel()->IsWithinTraverse( panel, x, y, false );
				if ( panel )
					return panel;
			}

			return GetVPanel();
		}
	}

	return NULL;
}

void Panel::GetInset( int &left, int &top, int &right, int &bottom )
{
	ipanel()->GetInset( GetVPanel(), left, top, right, bottom );
}

void Panel::GetClipRect( int &x0, int &y0, int &x1, int &y1 )
{
	ipanel()->GetClipRect( GetVPanel(), x0, y0, x1, y1 );
}

void Panel::OnChildAdded( VPANEL child )
{
}

void Panel::OnSizeChanged( int newWide, int newTall )
{
	InvalidateLayout();
}

void Panel::InternalFocusChanged( bool lost )
{
}

bool Panel::RequestInfo( KeyValues *outputData )
{
	if ( GetVParent() )
		return ipanel()->RequestInfo( GetVParent(), outputData );

	return false;
}

void Panel::RequestFocus( int direction )
{
	OnRequestFocus( GetVPanel(), NULL );
}

bool Panel::RequestFocusPrev( VPANEL panel )
{
	if ( GetVParent() )
		return ipanel()->RequestFocusPrev( GetVParent(), GetVPanel() );

	return false;
}

bool Panel::RequestFocusNext( VPANEL panel )
{
	if ( GetVParent() )
		return ipanel()->RequestFocusNext( GetVParent(), GetVPanel() );

	return false;
}

void Panel::OnMessage( const KeyValues *params, VPANEL ifromPanel )
{
	KeyValues *msg = params->MakeCopy();
	const char *msgName = msg->GetName();

	if ( !strcmp( msgName, "Repaint" ) )
		Repaint();
	else if ( !strcmp( msgName, "Command" ) )
		OnCommand( msg->GetString( "command", "" ) );
	else if ( !strcmp( msgName, "MouseCaptureLost" ) )
		OnMouseCaptureLost();
	else if ( !strcmp( msgName, "SetFocus" ) )
		OnSetFocus();
	else if ( !strcmp( msgName, "KillFocus" ) )
		OnKillFocus();
	else if ( !strcmp( msgName, "Delete" ) )
		OnDelete();
	else if ( !strcmp( msgName, "Tick" ) )
		OnTick();
	else if ( !strcmp( msgName, "OnCursorMoved" ) )
		OnCursorMoved( msg->GetInt( "x", 0 ), msg->GetInt( "y", 0 ) );
	else if ( !strcmp( msgName, "OnMouseFocusTicked" ) )
		OnMouseFocusTicked();
	else if ( !strcmp( msgName, "OnRequestFocus" ) )
		OnRequestFocus( msg->GetInt( "subFocus", 0 ), msg->GetInt( "defaultPanel", 0 ) );
	else if ( !strcmp( msgName, "CursorMoved" ) )
		InternalCursorMoved( msg->GetInt( "xpos", 0 ), msg->GetInt( "ypos", 0 ) );
	else if ( !strcmp( msgName, "CursorEntered" ) )
		InternalCursorEntered();
	else if ( !strcmp( msgName, "CursorExited" ) )
		InternalCursorExited();
	else if ( !strcmp( msgName, "MousePressed" ) )
		InternalMousePressed( (vgui2::MouseCode)msg->GetInt( "code", 0 ) );
	else if ( !strcmp( msgName, "MouseDoublePressed" ) )
		InternalMouseDoublePressed( (vgui2::MouseCode)msg->GetInt( "code", 0 ) );
	else if ( !strcmp( msgName, "MouseReleased" ) )
		InternalMouseReleased( (vgui2::MouseCode)msg->GetInt( "code", 0 ) );
	else if ( !strcmp( msgName, "MouseWheeled" ) )
		InternalMouseWheeled( msg->GetInt( "delta", 0 ) );
	else if ( !strcmp( msgName, "KeyCodePressed" ) )
		InternalKeyCodePressed( (vgui2::KeyCode)msg->GetInt( "code", 0 ) );
	else if ( !strcmp( msgName, "KeyCodeTyped" ) )
		InternalKeyCodeTyped( (vgui2::KeyCode)msg->GetInt( "code", 0 ) );
	else if ( !strcmp( msgName, "KeyTyped" ) )
		InternalKeyTyped( msg->GetInt( "unichar", 0 ) );
	else if ( !strcmp( msgName, "KeyCodeReleased" ) )
		InternalKeyCodeReleased( (vgui2::KeyCode)msg->GetInt( "code", 0 ) );
	else if ( !strcmp( msgName, "KeyFocusTicked" ) )
		InternalKeyFocusTicked();
	else if ( !strcmp( msgName, "MouseFocusTicked" ) )
		InternalMouseFocusTicked();
	else if ( !strcmp( msgName, "Invalidate" ) )
		InternalInvalidateLayout();
	else if ( !strcmp( msgName, "Move" ) )
		InternalMove();

	msg->deleteThis();
}

VPANEL Panel::GetCurrentKeyFocus()
{
	return NULL;
}

int Panel::GetTabPosition()
{
	return tabPosition;
}

const char *Panel::GetName()
{
	if ( name != nullptr )
		return name;

	return "";
}

const char *Panel::GetClassName()
{
	return "Panel";
}

HScheme Panel::GetScheme()
{
	if ( scheme != 0 )
		return scheme;

	if ( GetVParent() )
		return ipanel()->GetScheme( GetVParent() );

	return vgui2::scheme()->GetDefaultScheme();
}

bool Panel::IsProportional()
{
	return proportional;
}

bool Panel::IsAutoDeleteSet()
{
	return autoDelete;
}

void Panel::DeletePanel()
{
	delete this;
}

void *Panel::QueryInterface( EInterfaceID id )
{
	if ( id == ICLIENTPANEL_STANDARD_INTERFACE )
		return this;

	return nullptr;
}

Panel *Panel::GetPanel()
{
	return this;
}

const char *Panel::GetModuleName()
{
	return vgui2::GetModuleName();
}

VPANEL Panel::GetVParent()
{
	return ipanel()->GetParent( GetVPanel() );
}

void Panel::CallParentFunction( KeyValues *message )
{
	if ( GetVParent() )
		ipanel()->SendMessage( GetVParent(), message, GetVPanel() );

	if ( message )
		message->deleteThis();
}

void Panel::InvalidateLayout( bool layoutNow, bool reloadScheme )
{
	needsLayout = true;

	if ( reloadScheme )
	{
		needsSchemeUpdate = true;

		for ( int i = 0; i < GetChildCount(); i++ )
		{
			Panel *child = GetChild( i );
			if ( child != nullptr )
				child->InvalidateLayout( layoutNow, true );
		}

		PerformApplySchemeSettings();
	}

	if ( layoutNow )
		InternalPerformLayout();
}

int Panel::GetChildCount()
{
	return ipanel()->GetChildCount( GetVPanel() );
}

Panel *Panel::GetChild( int index )
{
	return ipanel()->GetPanel( ipanel()->GetChild( GetVPanel(), index ), vgui2::GetModuleName() );
}

void Panel::InternalPerformLayout()
{
	if ( needsSchemeUpdate )
		return;

	inPerformLayout = true;
	needsLayout = false;
	PerformLayout();
	inPerformLayout = false;
}

void Panel::PerformLayout()
{
}

bool Panel::IsVisible()
{
	return ipanel()->IsVisible( GetVPanel() );
}

bool Panel::IsMouseInputEnabled()
{
	return ipanel()->IsMouseInputEnabled( GetVPanel() );
}

bool Panel::IsKeyBoardInputEnabled()
{
	return ipanel()->IsKeyBoardInputEnabled( GetVPanel() );
}

bool Panel::IsWithin( int x, int y )
{
	int clipRect[4];
	ipanel()->GetClipRect( GetVPanel(), clipRect[0], clipRect[1], clipRect[2], clipRect[3] );

	if ( x < clipRect[0] )
		return false;

	if ( y < clipRect[1] )
		return false;

	if ( x >= clipRect[2] )
		return false;

	if ( y >= clipRect[3] )
		return false;

	return true;
}

void Panel::PaintBackground()
{
	int wide, tall;
	GetSize( wide, tall );
	surface()->DrawSetColor( GetBgColor() );
	surface()->DrawFilledRect( 0, 0, wide, tall );
}

void Panel::Paint()
{
}

void Panel::PaintBorder()
{
	border->Paint( GetVPanel() );
}

void Panel::PostChildPaint()
{
}

void Panel::OnThink()
{
}

void Panel::GetSize( int &wide, int &tall )
{
	return ipanel()->GetSize( GetVPanel(), wide, tall );
}

Color Panel::GetBgColor()
{
	return bgColor;
}

Color Panel::GetFgColor()
{
	return fgColor;
}

void Panel::SetBgColor( Color _bgColor )
{
	bgColor = _bgColor;
}

void Panel::SetFgColor( Color _fgColor )
{
	fgColor = _fgColor;
}

void Panel::ApplySchemeSettings( IScheme *pScheme )
{
	needsSchemeUpdate = false;
}

Color Panel::GetSchemeColor( const char *keyName, IScheme *pScheme )
{
	return pScheme->GetColor( keyName, Color( 255, 255, 255, 255 ) );
}

void Panel::SetParent( Panel *parent )
{
	if ( parent == nullptr )
		ipanel()->SetParent( GetVPanel(), NULL );
	else
		ipanel()->SetParent( GetVPanel(), parent->GetVPanel() );
}

void Panel::SetScheme( HScheme _scheme )
{
	if ( scheme != _scheme )
		scheme = _scheme;
}

void Panel::SetName( const char *_name )
{
	if ( name != nullptr && _name != nullptr && !strcmp( name, _name ) )
		return;

	if ( name != nullptr )
	{
		delete[] name;
		name = NULL;
	}

	if ( _name != nullptr )
	{
		int len = strlen( _name );
		name = new char[len + 1];
		strncpy( name, _name, len );
		name[len] = '\0';
	}
}

void Panel::OnCommand( const char *command )
{
}

void Panel::OnMouseCaptureLost()
{
}

void Panel::OnSetFocus()
{
	Repaint();
}

void Panel::OnKillFocus()
{
	Repaint();
}

void Panel::OnDelete()
{
	delete this;
}

void Panel::OnTick()
{
}

void Panel::OnCursorMoved( int x, int y )
{
}

void Panel::OnMouseFocusTicked()
{
	CallParentFunction( new KeyValues( "OnMouseFocusTicked" ) );
}

void Panel::OnRequestFocus( VPANEL subFocus, VPANEL defaultPanel )
{
	CallParentFunction( new KeyValues( "OnRequestFocus", "subFocus", subFocus, "defaultPanel", defaultPanel ) );
}

void Panel::InternalCursorMoved( int x, int y )
{
	if ( IsCursorNone() || !IsMouseInputEnabled() )
		return;

	ScreenToLocal( x, y );
	OnCursorMoved( x, y );
}

void Panel::InternalCursorEntered()
{
	if ( IsCursorNone() || !IsMouseInputEnabled() )
		return;

	OnCursorEntered();
}

void Panel::InternalCursorExited()
{
	if ( IsCursorNone() || !IsMouseInputEnabled() )
		return;

	OnCursorExited();
}

void Panel::InternalMousePressed( MouseCode code )
{
	if ( IsCursorNone() || !IsMouseInputEnabled() )
		return;

	OnMousePressed( code );
}

void Panel::InternalMouseDoublePressed( MouseCode code )
{
	if ( IsCursorNone() || !IsMouseInputEnabled() )
		return;

	OnMouseDoublePressed( code );
}

void Panel::InternalMouseReleased( MouseCode code )
{
	if ( IsCursorNone() || !IsMouseInputEnabled() )
		return;

	OnMouseReleased( code );
}

void Panel::InternalMouseWheeled( int delta )
{
	if ( !IsMouseInputEnabled() )
		return;

	OnMouseWheeled( delta );
}

void Panel::InternalKeyCodePressed( KeyCode code )
{
	if ( IsKeyBoardInputEnabled() )
		OnKeyCodePressed( code );
	else
		CallParentFunction( new KeyValues( "KeyCodePressed", "code", code ) );
}

void Panel::InternalKeyCodeTyped( KeyCode code )
{
	if ( IsKeyBoardInputEnabled() )
		OnKeyCodeTyped( code );
	else
		CallParentFunction( new KeyValues( "KeyCodeTyped", "code", code ) );
}

void Panel::InternalKeyTyped( int unichar )
{
	if ( IsKeyBoardInputEnabled() )
		OnKeyTyped( unichar );
	else
		CallParentFunction( new KeyValues( "KeyTyped", "unichar", unichar ) );
}

void Panel::InternalKeyCodeReleased( KeyCode code )
{
	if ( IsKeyBoardInputEnabled() )
		OnKeyCodeReleased( code );
	else
		CallParentFunction( new KeyValues( "KeyCodeReleased", "code", code ) );
}

void Panel::InternalKeyFocusTicked()
{
	OnKeyFocusTicked();
}

void Panel::InternalMouseFocusTicked()
{
	InternalSetCursor();
	OnMouseFocusTicked();
}

void Panel::InternalInvalidateLayout()
{
	InvalidateLayout( false, false );
}

void Panel::InternalMove()
{
	OnMove();

	for ( int i = 0; i < GetChildCount(); i++ )
		GetChild( i )->OnMove();
}

void Panel::SetCursor( HCursor _cursor )
{
	cursor = _cursor;
}

HCursor Panel::GetCursor()
{
	return cursor;
}

bool Panel::IsCursorNone()
{
	return GetCursor() == NULL;
}

void Panel::ScreenToLocal( int &x, int &y )
{
	int px, py;
	ipanel()->GetAbsPos( GetVPanel(), px, py );

	x = x - px;
	y = y - py;
}

void Panel::OnCursorEntered()
{
}

void Panel::OnCursorExited()
{
}

void Panel::OnMousePressed( MouseCode code )
{
}

void Panel::OnMouseDoublePressed( MouseCode code )
{
}

void Panel::OnMouseReleased( MouseCode code )
{
}

void Panel::OnMouseWheeled( int delta )
{
	CallParentFunction( new KeyValues( "MouseWheeled", "delta", delta ) );
}

void Panel::OnKeyCodePressed( KeyCode code )
{
	CallParentFunction( new KeyValues( "KeyCodePressed", "code", code ) );
}

void Panel::OnKeyCodeTyped( KeyCode code )
{
	if ( code != KEY_TAB )
	{
		CallParentFunction( new KeyValues( "KeyCodeTyped", "code", code ) );
		return;
	}

	if ( input()->IsKeyDown( KEY_LSHIFT ) || input()->IsKeyDown( KEY_RSHIFT ) )
		RequestFocusPrev( NULL );
	else
		RequestFocusNext( NULL );
}

void Panel::OnKeyTyped( int unichar )
{
	CallParentFunction( new KeyValues( "KeyTyped", "unichar", unichar ) );
}

void Panel::OnKeyCodeReleased( KeyCode code )
{
	CallParentFunction( new KeyValues( "KeyCodeReleased", "code", code ) );
}

void Panel::OnKeyFocusTicked()
{
	CallParentFunction( new KeyValues( "KeyFocusTicked" ) );
}

void Panel::InternalSetCursor()
{
	bool visible = IsVisible();
	if ( !visible )
		return;

	VPANEL p = GetVParent();
	while ( p )
	{
		visible &= ipanel()->IsVisible( p );
		p = ipanel()->GetParent( p );
	}

	if ( visible && HasParent( surface()->GetEmbeddedPanel() ) )
	{
		HCursor cursor = GetCursor();

		if ( input()->GetCursorOveride() )
			cursor = input()->GetCursorOveride();

		surface()->SetCursor( cursor );
	}
}

void Panel::OnMove()
{
}

bool Panel::HasParent( VPANEL potentialParent )
{
	if ( !potentialParent )
		return false;

	return ipanel()->HasParent( GetVPanel(), potentialParent );
}

void Panel::SetBounds( int x, int y, int wide, int tall )
{
	SetPos( x, y );
	SetSize( wide, tall );
}

void Panel::SetPos( int x, int y )
{
	ipanel()->SetPos( GetVPanel(), x, y );
}

void Panel::SetSize( int wide, int tall )
{
	ipanel()->SetSize( GetVPanel(), wide, tall );
}

void Panel::SetPaintBorderEnabled( bool state )
{
	paintBorderEnabled = state;
}

void Panel::SetPaintBackgroundEnabled( bool state )
{
	paintBackgroundEnabled = state;
}

void Panel::SetPaintEnabled( bool state )
{
	paintEnabled = state;
}

void Panel::SetVisible( bool state )
{
	ipanel()->SetVisible( GetVPanel(), state );
}

void Panel::SetZPos( int zpos )
{
	ipanel()->SetZPos( GetVPanel(), zpos );
}

void Panel::SetScheme( const char *tag )
{
	if ( strlen( tag ) > 0 && vgui2::scheme()->GetScheme( tag ) )
		SetScheme( vgui2::scheme()->GetScheme( tag ) );
}

} // namespace vgui2
