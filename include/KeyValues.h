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
