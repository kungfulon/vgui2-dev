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

#ifndef KEYVALUES_H
#define KEYVALUES_H

#include <stddef.h>

class IFileSystem;

class KeyValues
{
public:
	enum types_t
	{
		TYPE_NONE = 0,
		TYPE_STRING = 1,
		TYPE_INT = 2,
		TYPE_FLOAT = 3,
		TYPE_PTR = 4,
		TYPE_WSTRING = 5,
		TYPE_COLOR = 6,
		TYPE_UINT64 = 7,
	};

	KeyValues( const char *name );
	KeyValues( const char *name, const char *firstKey, const char *firstValue );
	KeyValues( const char *name, const char *firstKey, const wchar_t *firstValue );
	KeyValues( const char *name, const char *firstKey, int firstValue );
	KeyValues( const char *name, const char *firstKey, const char *firstValue, const char *secondKey, const char *secondValue );
	KeyValues( const char *name, const char *firstKey, int firstValue, const char *secondKey, int secondValue );

	~KeyValues();

	void Init( const char *name );
	void AllocateValueBlock( int iAllocSize );
	void FreeAllocatedValue();

	virtual const char *GetName() const;
	virtual int GetNameSymbol() const;
	virtual bool LoadFromFile( IFileSystem *filesystem, const char *resourceName, const char *pathID );
	virtual bool SaveToFile( IFileSystem *filesystem, const char *resourceName, const char *pathID );
	virtual KeyValues *FindKey( const char *keyName, bool bCreate );
	virtual KeyValues *FindKey( int keySymbol ) const;
	virtual KeyValues *CreateNewKey();
	virtual void RemoveSubKey( KeyValues *subKey );
	virtual KeyValues *GetFirstSubKey();
	virtual KeyValues *GetNextKey();
	virtual int GetInt( const char *keyName, int defaultValue );
	virtual float GetFloat( const char *keyName, float defaultValue );
	virtual const char *GetString( const char *keyName, const char *defaultValue );
	virtual const wchar_t *GetWString( const char *keyName, const wchar_t *defaultValue );
	virtual void *GetPtr( const char *keyName, void *defaultValue );
	virtual bool IsEmpty( const char *keyName );
	virtual void SetWString( const char *keyName, const wchar_t *value );
	virtual void SetString( const char *keyName, const char *value );
	virtual void SetInt( const char *keyName, int value );
	virtual void SetFloat( const char *keyName, float value );
	virtual void SetPtr( const char *keyName, void *value );
	virtual KeyValues *MakeCopy() const;
	virtual void Clear();
	virtual types_t GetDataType( const char *keyName );
	virtual void deleteThis();

	void *operator new( size_t iAllocSize );
	void operator delete( void *pMem );

private:
	int m_iKeyName;

	union {
		int m_iValue;
		float m_flValue;
		void *m_pValue;
		char *m_sValue;
		unsigned char m_Color[4];
	};

	unsigned short m_iDataType;

	short m_iAllocationSize;

	KeyValues *m_pPeer;
	KeyValues *m_pSub;
};

#endif // KEYVALUES_H
