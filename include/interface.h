#ifndef INTERFACE_H
#define INTERFACE_H

// HACK: Detect Xash3D FWGS
#ifdef VFILESYSTEM009_H
class IBaseInterface;
#else
class IBaseInterface
{
public:
	virtual ~IBaseInterface() {}
};
#endif

typedef IBaseInterface* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

enum 
{
	IFACE_OK = 0,
	IFACE_FAILED
};

#endif
