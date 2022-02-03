#ifndef ISCHEME_H
#define ISCHEME_H

#include "Color.h"
#include "VGUI2.h"
#include "interface.h"

namespace vgui2
{

class IBorder;
class IImage;

class IScheme : public IBaseInterface
{
public:
	virtual const char *GetResourceString( const char *stringName ) = 0;
	virtual IBorder *GetBorder( const char *borderName ) = 0;
	virtual HFont GetFont( const char *fontName, bool proportional ) = 0;
	virtual Color GetColor( const char *colorName, Color defaultColor ) = 0;
};

class ISchemeManager : public IBaseInterface
{
public:
	virtual HScheme LoadSchemeFromFile( const char *fileName, const char *tag ) = 0;
	virtual void ReloadSchemes() = 0;
	virtual HScheme GetDefaultScheme() = 0;
	virtual HScheme GetScheme( const char *tag ) = 0;
	virtual IImage *GetImage( const char *imageName, bool hardwareFiltered ) = 0;
	virtual HTexture GetImageID( const char *imageName, bool hardwareFiltered ) = 0;
	virtual class IScheme *GetIScheme( HScheme scheme ) = 0;
	virtual void Shutdown( bool full ) = 0;
	virtual int GetProportionalScaledValue( int normalizedValue ) = 0;
	virtual int GetProportionalNormalizedValue( int scaledValue ) = 0;
};

#define VGUI_SCHEME_INTERFACE_VERSION "VGUI_Scheme009"

}; // namespace vgui2

#endif // ISCHEME_H
