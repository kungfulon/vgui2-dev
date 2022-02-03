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
