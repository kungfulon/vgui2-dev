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

#ifndef IVGUI_H
#define IVGUI_H

#include "IAppSystem.h"
#include "VGUI2.h"
#include "interface.h"

class KeyValues;

namespace vgui2
{

typedef unsigned long HPanel;
typedef int HContext;

class IVGui : public IBaseInterface, public IAppSystem
{
public:
	virtual bool Init( CreateInterfaceFn *factoryList, int numFactories ) = 0;
	virtual void Shutdown() = 0;
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual bool IsRunning() = 0;
	virtual void RunFrame() = 0;
	virtual void ShutdownMessage( unsigned int shutdownID ) = 0;
	virtual VPANEL AllocPanel() = 0;
	virtual void FreePanel( VPANEL ) = 0;
	virtual void DPrintf( const char *format, ... ) = 0;
	virtual void DPrintf2( const char *format, ... ) = 0;
	virtual void SpewAllActivePanelNames() = 0;
	virtual HPanel PanelToHandle( VPANEL panel ) = 0;
	virtual VPANEL HandleToPanel( HPanel index ) = 0;
	virtual void MarkPanelForDeletion( VPANEL panel ) = 0;
	virtual void AddTickSignal( VPANEL panel, int intervalMilliseconds ) = 0;
	virtual void RemoveTickSignal( VPANEL panel ) = 0;
	virtual void PostMessage( VPANEL target, KeyValues *params, VPANEL from, float delaySeconds ) = 0;
	virtual HContext CreateContext() = 0;
	virtual void DestroyContext( HContext context ) = 0;
	virtual void AssociatePanelWithContext( HContext context, VPANEL pRoot ) = 0;
	virtual void ActivateContext( HContext context ) = 0;
	virtual void SetSleep( bool state ) = 0;
	virtual bool GetShouldVGuiControlSleep() = 0;
};

#define VGUI_IVGUI_INTERFACE_VERSION "VGUI_ivgui006"

} // namespace vgui2

#endif // IVGUI_H
