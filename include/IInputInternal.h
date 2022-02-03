#ifndef IINPUTINTERNAL_H
#define IINPUTINTERNAL_H

#include "IInput.h"

namespace vgui2
{

typedef int HInputContext;

class IInputInternal : public IInput
{
public:
	virtual void RunFrame() = 0;
	virtual void UpdateMouseFocus( int x, int y ) = 0;
	virtual void PanelDeleted( VPANEL panel ) = 0;
	virtual void InternalCursorMoved( int x, int y ) = 0;
	virtual void InternalMousePressed( MouseCode code ) = 0;
	virtual void InternalMouseDoublePressed( MouseCode code ) = 0;
	virtual void InternalMouseReleased( MouseCode code ) = 0;
	virtual void InternalMouseWheeled( int delta ) = 0;
	virtual void InternalKeyCodePressed( KeyCode code ) = 0;
	virtual void InternalKeyCodeTyped( KeyCode code ) = 0;
	virtual void InternalKeyTyped( wchar_t unichar ) = 0;
	virtual void InternalKeyCodeReleased( KeyCode code ) = 0;
	virtual HInputContext CreateInputContext() = 0;
	virtual void DestroyInputContext( HInputContext context ) = 0;
	virtual void AssociatePanelWithInputContext( HInputContext context, VPANEL pRoot ) = 0;
	virtual void ActivateInputContext( HInputContext context ) = 0;
};

#define VGUI_INPUTINTERNAL_INTERFACE_VERSION "VGUI_InputInternal001"

} // namespace vgui2

#endif // IINPUTINTERNAL_H
