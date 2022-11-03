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

#ifndef VGUIVERTEX_H
#define VGUIVERTEX_H

namespace vgui2
{

class VGuiVertex
{
public:
	VGuiVertex() : x( 0 ), y( 0 ), u( 0.0f ), v( 0.0f ) {}
	VGuiVertex( int x, int y, float u, float v ) : x( x ), y( y ), u( u ), v( v ) {}

	void SetVertex( int _x, int _y )
	{
		x = _x;
		y = _y;
	}

	void SetVertex( int _x, int _y, float _u, float _v )
	{
		x = _x;
		y = _y;
		u = _u;
		v = _v;
	}

	int GetX() { return x; }
	int GetY() { return y; }
	float GetU() { return u; }
	float GetV() { return v; }

	void GetVertex( int &_x, int _y, float &_u, float &_v )
	{
		_x = x;
		_y = y;
		_u = u;
		_v = v;
	}

	bool operator==( VGuiVertex &o ) const
	{
		return x == o.x && y == o.y && u == o.u && v == o.v;
	}

private:
	int x;
	int y;
	float u;
	float v;
};

} // namespace vgui2

#endif // VGUIVERTEX_H
