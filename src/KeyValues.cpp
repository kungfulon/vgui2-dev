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

#include "KeyValues.h"
#include "VGui2Interfaces.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#ifndef ARRAYSIZE
#define ARRAYSIZE( x ) ( sizeof( x ) / sizeof( *( x ) ) )
#endif // ARRAYSIZE

KeyValues::KeyValues( const char *name )
{
	Init( name );
}

KeyValues::KeyValues( const char *name, const char *firstKey, const char *firstValue )
{
	Init( name );
	SetString( firstKey, firstValue );
}

KeyValues::KeyValues( const char *name, const char *firstKey, const wchar_t *firstValue )
{
	Init( name );
	SetWString( firstKey, firstValue );
}

KeyValues::KeyValues( const char *name, const char *firstKey, int firstValue )
{
	Init( name );
	SetInt( firstKey, firstValue );
}

KeyValues::KeyValues( const char *name, const char *firstKey, const char *firstValue, const char *secondKey, const char *secondValue )
{
	Init( name );
	SetString( firstKey, firstValue );
	SetString( secondKey, secondValue );
}

KeyValues::KeyValues( const char *name, const char *firstKey, int firstValue, const char *secondKey, int secondValue )
{
	Init( name );
	SetInt( firstKey, firstValue );
	SetInt( secondKey, secondValue );
}

KeyValues::~KeyValues()
{
	KeyValues *dat;
	KeyValues *datNext = nullptr;

	for ( dat = m_pSub; dat != nullptr; dat = datNext )
	{
		datNext = dat->m_pPeer;
		delete dat;
	}

	for ( dat = m_pPeer; dat && dat != this; dat = datNext )
	{
		datNext = dat->m_pPeer;
		delete dat;
	}

	m_pSub = nullptr;
	m_pPeer = nullptr;
	FreeAllocatedValue();
}

void KeyValues::Init( const char *name )
{
	m_iKeyName = keyvalues()->GetSymbolForString( name );
	m_iDataType = TYPE_NONE;
	m_pSub = nullptr;
	m_pPeer = nullptr;
	m_sValue = nullptr;
	m_iAllocationSize = 0;
}

void KeyValues::AllocateValueBlock( int iAllocSize )
{
	if ( iAllocSize <= sizeof( KeyValues ) )
		m_sValue = (char *)keyvalues()->AllocKeyValuesMemory( iAllocSize );
	else
		m_sValue = new char[iAllocSize];

	m_iAllocationSize = iAllocSize;
}

void KeyValues::FreeAllocatedValue()
{
	if ( m_iAllocationSize == 0 )
		return;

	if ( m_iAllocationSize <= sizeof( KeyValues ) )
		keyvalues()->FreeKeyValuesMemory( m_sValue );
	else if ( m_sValue != nullptr )
		delete[] m_sValue;

	m_sValue = nullptr;
	m_iAllocationSize = 0;
}

const char *KeyValues::GetName() const
{
	return keyvalues()->GetStringForSymbol( m_iKeyName );
}

int KeyValues::GetNameSymbol() const
{
	return m_iKeyName;
}

bool KeyValues::LoadFromFile( IFileSystem *filesystem, const char *resourceName, const char *pathID )
{
	return false;
}

bool KeyValues::SaveToFile( IFileSystem *filesystem, const char *resourceName, const char *pathID )
{
	return false;
}

KeyValues *KeyValues::FindKey( const char *keyName, bool bCreate )
{
	if ( keyName == nullptr || *keyName == '\0' )
		return this;

	char buf[256];
	const char *subStr = strchr( keyName, '/' );
	const char *searchStr = keyName;

	if ( subStr != nullptr )
	{
		int size = subStr - keyName;
		memcpy( buf, keyName, size );
		buf[size] = 0;
		searchStr = buf;
	}

	HKeySymbol searchSymbol = keyvalues()->GetSymbolForString( searchStr );

	KeyValues *lastItem = nullptr;
	KeyValues *dat;
	for ( dat = m_pSub; dat != NULL; dat = dat->m_pPeer )
	{
		lastItem = dat;

		if ( dat->m_iKeyName == searchSymbol )
			break;
	}

	if ( dat != nullptr )
	{
		if ( !bCreate )
			return nullptr;

		dat = new KeyValues( searchStr );

		if ( lastItem != nullptr )
			lastItem->m_pPeer = dat;
		else
			m_pSub = dat;

		m_iDataType = TYPE_NONE;
	}

	if ( subStr != nullptr )
		dat->FindKey( subStr + 1, bCreate );

	return dat;
}

KeyValues *KeyValues::FindKey( int keySymbol ) const
{
	for ( auto dat = m_pSub; dat != nullptr; dat = dat->m_pPeer )
	{
		if ( dat->m_iKeyName == keySymbol )
			return dat;
	}
	return nullptr;
}

KeyValues *KeyValues::CreateNewKey()
{
	int newID = 1;

	for ( auto dat = m_pSub; dat != nullptr; dat = dat->m_pPeer )
	{
		int val = atoi( dat->GetName() );
		if ( newID <= val )
			newID = val + 1;
	}

	char buf[12];
	snprintf( buf, sizeof( buf ), "%d", newID );
	return FindKey( buf, true );
}

void KeyValues::RemoveSubKey( KeyValues *subKey )
{
	if ( subKey == nullptr )
		return;

	if ( m_pSub == subKey )
	{
		m_pSub = subKey->m_pPeer;
		subKey->m_pPeer = nullptr;
		return;
	}

	KeyValues *kv = m_pSub;
	for ( auto kv = m_pSub; kv->m_pPeer != nullptr; kv = kv->m_pPeer )
	{
		if ( kv->m_pPeer == subKey )
		{
			kv->m_pPeer = subKey->m_pPeer;
			break;
		}
	}

	subKey->m_pPeer = nullptr;
}

KeyValues *KeyValues::GetFirstSubKey()
{
	return m_pSub;
}

KeyValues *KeyValues::GetNextKey()
{
	return m_pPeer;
}

int KeyValues::GetInt( const char *keyName, int defaultValue )
{
	KeyValues *dat = FindKey( keyName, false );
	if ( dat == nullptr )
		return defaultValue;

	switch ( dat->m_iDataType )
	{
	case TYPE_STRING:
		return atoi( dat->m_sValue );
	case TYPE_WSTRING:
		return wcstol( (wchar_t *)dat->m_sValue, NULL, 10 );
	case TYPE_FLOAT:
		return (int)dat->m_flValue;
	case TYPE_UINT64:
		return 0;
	};

	return dat->m_iValue;
}

float KeyValues::GetFloat( const char *keyName, float defaultValue )
{
	KeyValues *dat = FindKey( keyName, false );
	if ( dat == nullptr )
		return defaultValue;

	switch ( dat->m_iDataType )
	{
	case TYPE_STRING:
		return (float)atof( dat->m_sValue );
	case TYPE_FLOAT:
		return dat->m_flValue;
	case TYPE_INT:
		return (float)dat->m_iValue;
	case TYPE_UINT64:
		return (float)( *( (uint64_t *)dat->m_sValue ) );
	};

	return 0.0f;
}

const char *KeyValues::GetString( const char *keyName, const char *defaultValue )
{
	KeyValues *dat = FindKey( keyName, false );
	if ( dat == nullptr )
		return defaultValue;

	char buf[64];
	switch ( dat->m_iDataType )
	{
	case TYPE_FLOAT:
		snprintf( buf, sizeof( buf ), "%f", dat->m_flValue );
		SetString( keyName, buf );
		break;
	case TYPE_INT:
	case TYPE_PTR:
		snprintf( buf, sizeof( buf ), "%d", dat->m_iValue );
		SetString( keyName, buf );
		break;
	case TYPE_UINT64:
		snprintf( buf, sizeof( buf ), "%I64i", *( (uint64_t *)( dat->m_sValue ) ) );
		SetString( keyName, buf );
		break;
	case TYPE_WSTRING:
		keyvalues()->GetANSIFromLocalized( (wchar_t *)dat->m_sValue, buf, sizeof( buf ) );
		SetString( keyName, buf );
		break;
	case TYPE_STRING:
		return dat->m_sValue;
	};

	return defaultValue;
}

const wchar_t *KeyValues::GetWString( const char *keyName, const wchar_t *defaultValue )
{
	KeyValues *dat = FindKey( keyName, false );
	if ( dat == nullptr )
		return defaultValue;

	wchar_t wbuf[64];
	switch ( dat->m_iDataType )
	{
	case TYPE_FLOAT:
		swprintf( wbuf, ARRAYSIZE( wbuf ), L"%f", dat->m_flValue );
		SetWString( keyName, wbuf );
		break;
	case TYPE_INT:
	case TYPE_PTR:
		swprintf( wbuf, ARRAYSIZE( wbuf ), L"%d", dat->m_iValue );
		SetWString( keyName, wbuf );
		break;
	case TYPE_UINT64:
		swprintf( wbuf, ARRAYSIZE( wbuf ), L"%I64i", *( (uint64_t *)( dat->m_sValue ) ) );
		SetWString( keyName, wbuf );
		break;
	case TYPE_STRING:
		keyvalues()->GetLocalizedFromANSI( dat->m_sValue, wbuf, sizeof( wbuf ) );
		SetWString( keyName, wbuf );
		break;
	case TYPE_WSTRING:
		return (const wchar_t *)dat->m_sValue;
	}

	return defaultValue;
}

void *KeyValues::GetPtr( const char *keyName, void *defaultValue )
{
	KeyValues *dat = FindKey( keyName, false );
	if ( dat == nullptr )
		return defaultValue;
	return dat->m_iDataType == TYPE_PTR ? dat->m_pValue : nullptr;
}

bool KeyValues::IsEmpty( const char *keyName )
{
	auto dat = FindKey( keyName, false );
	if ( dat == nullptr )
		return true;
	if ( dat->m_iDataType == TYPE_NONE )
		return m_pSub == nullptr;
	return false;
}

void KeyValues::SetWString( const char *keyName, const wchar_t *value )
{
	KeyValues *dat = FindKey( keyName, false );
	if ( dat == nullptr )
		return;

	dat->FreeAllocatedValue();

	if ( value == nullptr )
		value = L"";

	int allocSize = ( wcslen( value ) + 1 ) * sizeof( wchar_t );
	dat->AllocateValueBlock( allocSize );
	memcpy( dat->m_sValue, value, allocSize );
	dat->m_iDataType = TYPE_WSTRING;
}

void KeyValues::SetString( const char *keyName, const char *value )
{
	KeyValues *dat = FindKey( keyName, false );
	if ( dat == nullptr )
		return;

	dat->FreeAllocatedValue();

	if ( value == nullptr )
		value = "";

	int allocSize = ( strlen( value ) + 1 ) * sizeof( char );
	dat->AllocateValueBlock( allocSize );
	memcpy( dat->m_sValue, value, allocSize );
	dat->m_iDataType = TYPE_STRING;
}

void KeyValues::SetInt( const char *keyName, int value )
{
	KeyValues *dat = FindKey( keyName, false );
	if ( dat == nullptr )
		return;

	dat->FreeAllocatedValue();
	dat->m_iValue = value;
	dat->m_iDataType = TYPE_INT;
}

void KeyValues::SetFloat( const char *keyName, float value )
{
	KeyValues *dat = FindKey( keyName, false );
	if ( dat == nullptr )
		return;

	dat->FreeAllocatedValue();
	dat->m_flValue = value;
	dat->m_iDataType = TYPE_FLOAT;
}

void KeyValues::SetPtr( const char *keyName, void *value )
{
	KeyValues *dat = FindKey( keyName, false );
	if ( dat == nullptr )
		return;

	dat->FreeAllocatedValue();
	dat->m_pValue = value;
	dat->m_iDataType = TYPE_PTR;
}

KeyValues *KeyValues::MakeCopy() const
{
	KeyValues *newKeyValue = new KeyValues( GetName() );
	newKeyValue->m_iDataType = m_iDataType;

	switch ( m_iDataType )
	{
	case TYPE_STRING:
		if ( m_sValue != nullptr )
		{
			int allocSize = ( strlen( m_sValue ) + 1 ) * sizeof( char );
			newKeyValue->AllocateValueBlock( allocSize );
			memcpy( newKeyValue->m_sValue, m_sValue, allocSize );
		}
		break;
	case TYPE_WSTRING:
		if ( m_sValue != nullptr )
		{
			int allocSize = ( wcslen( (wchar_t *)m_sValue ) + 1 ) * sizeof( wchar_t );
			newKeyValue->AllocateValueBlock( allocSize );
			memcpy( newKeyValue->m_sValue, m_sValue, allocSize );
		}
		break;
	case TYPE_INT:
		newKeyValue->m_iValue = m_iValue;
		break;
	case TYPE_FLOAT:
		newKeyValue->m_flValue = m_flValue;
		break;
	case TYPE_PTR:
		newKeyValue->m_pValue = m_pValue;
		break;
	case TYPE_COLOR:
		newKeyValue->m_Color[0] = m_Color[0];
		newKeyValue->m_Color[1] = m_Color[1];
		newKeyValue->m_Color[2] = m_Color[2];
		newKeyValue->m_Color[3] = m_Color[3];
		break;
	case TYPE_UINT64:
		newKeyValue->AllocateValueBlock( sizeof( uint64_t ) );
		memcpy( newKeyValue->m_sValue, m_sValue, sizeof( uint64_t ) );
		break;
	}

	KeyValues *pPrev = nullptr;
	for ( KeyValues *sub = m_pSub; sub != nullptr; sub = sub->m_pPeer )
	{
		KeyValues *dat = sub->MakeCopy();

		if ( pPrev )
			pPrev->m_pPeer = dat;
		else
			newKeyValue->m_pSub = dat;

		dat->m_pPeer = nullptr;
		pPrev = dat;
	}

	return newKeyValue;
}

void KeyValues::Clear()
{
	delete m_pSub;
	m_pSub = nullptr;
	FreeAllocatedValue();
	m_iDataType = TYPE_NONE;
}

KeyValues::types_t KeyValues::GetDataType( const char *keyName )
{
	auto dat = FindKey( keyName, false );
	return dat != nullptr ? (KeyValues::types_t)dat->m_iDataType : TYPE_NONE;
}

void KeyValues::deleteThis()
{
	delete this;
}

void *KeyValues::operator new( size_t iAllocSize )
{
	return keyvalues()->AllocKeyValuesMemory( iAllocSize );
}

void KeyValues::operator delete( void *pMem )
{
	keyvalues()->FreeKeyValuesMemory( pMem );
}
