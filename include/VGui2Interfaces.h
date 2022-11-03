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

#ifndef VGUI2INTERFACES_H
#define VGUI2INTERFACES_H

// HACK: Detect Xash3D FWGS
#ifdef XASH_BUILD_COMMIT
#include "VFileSystem009.h"
#else
#include "FileSystem.h"
#endif
#include "IInput.h"
#include "IInputInternal.h"
#include "IKeyValues.h"
#include "ILocalize.h"
#include "IPanel.h"
#include "IScheme.h"
#include "ISurface.h"
#include "ISystem.h"
#include "IVGui.h"
#include "interface.h"

IKeyValues *keyvalues();

namespace vgui2
{

IVGui *ivgui();
ILocalize *localize();
IFileSystem *filesystem();
IPanel *ipanel();
ISurface *surface();
ISchemeManager *scheme();
ISystem *system();
IInput *input();
IInputInternal *inputinternal();

bool InitializeVGui2Interfaces( const char *moduleName, CreateInterfaceFn *factories, int factoryCount );
const char *GetModuleName();

}; // namespace vgui2

#endif // VGUI2INTERFACES_H
