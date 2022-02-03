#ifndef IBORDER_H
#define IBORDER_H

#include "VGUI2.h"

class KeyValues;

namespace vgui2
{

class IScheme;

class IBorder
{
public:
	virtual void Paint( VPANEL panel ) = 0;
	virtual void Paint( int x, int y, int wide, int tall ) = 0;
	virtual void Paint( int x, int y, int wide, int tall, int breakSide, int breakStart, int breakEnd ) = 0;
	virtual void SetInset( int left, int top, int right, int bottom ) = 0;
	virtual void GetInset( int &left, int &top, int &right, int &bottom ) = 0;
	virtual void ApplySchemeSettings( IScheme *pScheme, KeyValues *inResourceData ) = 0;
	virtual const char *GetName() = 0;
	virtual void SetName( const char *name ) = 0;
};

} // namespace vgui2

#endif // IBORDER_H
