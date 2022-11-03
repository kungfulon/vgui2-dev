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
