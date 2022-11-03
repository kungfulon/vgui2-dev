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

#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
	Color() { SetColor( 0, 0, 0, 0 ); }
	Color( int r, int g, int b ) { SetColor( r, g, b, 0 ); }
	Color( int r, int g, int b, int a ) { SetColor( r, g, b, a ); }

	void SetColor( int r, int g, int b, int a )
	{
		_color[0] = r;
		_color[1] = g;
		_color[2] = b;
		_color[3] = a;
	}

	void GetColor( int &r, int &g, int &b, int &a ) const
	{
		r = _color[0];
		g = _color[1];
		b = _color[2];
		a = _color[3];
	}

	void SetRawColor( int color32 ) { *(int *)_color = color32; }

	int GetRawColor() const { return *(int *)_color; }

	int r() const { return _color[0]; }
	int g() const { return _color[1]; }
	int b() const { return _color[2]; }
	int a() const { return _color[3]; }

	unsigned char &operator[]( int index ) { return _color[index]; }

	bool operator==( const Color &rhs ) const { return GetRawColor() == rhs.GetRawColor(); }

	bool operator!=( Color &rhs ) const { return GetRawColor() != rhs.GetRawColor(); }

private:
	unsigned char _color[4];
};

#endif // COLOR_H
