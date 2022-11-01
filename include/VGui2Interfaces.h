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
