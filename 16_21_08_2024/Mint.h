#pragma once

#include "ostream"
#include "istream"

class Mint
{
public:
	Mint() = default;
	explicit Mint(int x) : mval{ x } {}
	// s�n�f�n i�inde tan�mlansalarda member function de�iller ��nk� friend fonksiyonlar yani global

	// symetric binary operators
	friend Mint operator+(const Mint& lhs, const Mint& rhs)  
	{
		return Mint{ lhs } += rhs; // aritmetik operat�rlerin ovarload edilmesinde scott mayers�n effective C++ kitab�nda �ok g�zel bir yakla��m var hoca bu yakla��m� kullanacak
								   // + ile += birbirine �ok benziyor bu y�zden += fonksiyonunu yazal�m bunuda + fonksiyonunda �a��raca��z
	}
	friend Mint operator-(const Mint& lhs, const Mint& rhs)
	{
		return Mint{ lhs } -= rhs;
	}
	friend Mint operator*(const Mint& lhs, const Mint& rhs)
	{
		return Mint{ lhs } *= rhs;

	}
	friend Mint operator/(const Mint& lhs, const Mint& rhs)
	{
		return Mint{ lhs } /= rhs;

	}
	friend Mint operator%(const Mint& lhs, const Mint& rhs)
	{
		return Mint{ lhs } %= rhs;

	}

	// equality operators/relations operators
	// C++20 kullanm�yorsak hepsini ayr� ayr� implemente etmek yerine == fonksiyonunu implemente ediyoruz != foknsiyonu == fonksiyonunu �a��r�yor gibi gibi
	friend bool operator==(const Mint& lhs, const Mint& rhs)
	{
		return lhs == rhs;
	}
	friend bool operator!=(const Mint& lhs, const Mint& rhs)
	{
		return !(lhs == rhs); // derleyici burda yeni bir fonksiyon yazm�yor yazm�� oldu�umuz == operat�r fonksiyonunun ! ifadesini al�yor
		// return !operator==(lhs,rhs); // baz� programc�lar b�yle yazmay� tercih ediyor
	}
	friend bool operator<(const Mint& lhs, const Mint& rhs)
	{
		return lhs.mval < rhs.mval;
	}
	friend bool operator>=(const Mint& lhs, const Mint& rhs)
	{
		return !(lhs < rhs); // operator >= operator < fonksiyonunu �a��rd�
	}
	friend bool operator>(const Mint& lhs, const Mint& rhs)
	{
		return rhs < lhs;
	}
	friend bool operator<=(const Mint& lhs, const Mint& rhs)
	{
		return !(rhs < lhs);
	}

	// assigned operators
	Mint& operator+=(const Mint& other) // s�n�fa yaz�lan atama operat�r fonksiyonlar� geri d�n�� de�eri s�n�f t�r�nden l value reference olmas� gerekir
	{
		mval += other.mval;
		return *this;
	}
	Mint& operator-=(const Mint& other)
	{
		mval -= other.mval;
		return *this;
	}
	Mint& operator*=(const Mint& other)
	{
		mval *= other.mval;
		return *this;
	}
	Mint& operator/=(const Mint& other)
	{
		mval /= other.mval;
		return *this;
	}
	Mint& operator%=(const Mint& other)
	{
		mval %= other.mval;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Mint& m) // inserter
	{
		return os << '[' << m.mval << ']'; // ostream s�n�f�n�n int parametreli << fonksiyonunu �a��r�yor
	}

	friend std::istream& operator>>(std::istream& is, Mint& m) // extraction
	{
		return is >> m.mval;
		// bu implementasyonlar� cpp dosyas�ndada yapabiliriz iosfwd ad�nda ba�l�k dosyas�n� kullanmam�z gerekir kodlar�n kendileri yok ama onlar�n forward declerationu var
	}

	Mint operator+() const
	{
		return *this;
	}

	Mint operator-() const
	{
		return Mint(-mval);
	}

	bool operator!() const
	{
		return static_cast<bool>(mval);
	}

	Mint& operator++() // prefix
	{
		++mval;
		return *this;
	}

	Mint operator++(int) // postfix
	{
		 Mint retval { *this };
		 ++*this; // nesnenin de�erini 1 artt�rmak i�in prefix fonksiyonunu �a��r�yor bu ifadeyi yazmak yerinede operator++() �eklinde yazabiliriz
		 return retval; 
	}

	int get()const
	{
		return mval;
	}

	Mint& operator--() // prefix
	{
		--mval;
		return *this;
	}

	Mint operator--(int) // postfix
	{
		Mint retval{ *this };
		--*this; 
		return retval;
	}
	
	explicit operator int() const
	{
		return mval;
	}
private:
	int mval{};
};
