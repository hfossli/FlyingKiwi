// Author: Håvard Fossli <hfossli@gmail.com>
//
// Copyright (c) 2013 Agens AS (http://agens.no/)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once


namespace FlyingKiwi
{

class SharedData
{

public:

    SharedData() : m_refcount( 0 ) {}

    SharedData( const SharedData& other ) : m_refcount( 0 ) {}

    int m_refcount;

private:

    SharedData& operator=( const SharedData& other );
};


template<typename T>
class SharedDataPtr
{

public:

	typedef T Type;

	SharedDataPtr() : m_data( 0 ) {}

	explicit SharedDataPtr( T* data ) : m_data( data )
	{
		incref( m_data );
	}

	~SharedDataPtr()
	{
		decref( m_data );
	}

	T* data()
	{
		return m_data;
	}

	const T* data() const
	{
		return m_data;
	}

	operator T*()
	{
		return m_data;
	}

	operator const T*() const
	{
		return m_data;
	}

	T* operator->()
	{
		return m_data;
	}

	const T* operator->() const
	{
		return m_data;
	}

	T& operator*()
	{
		return *m_data;
	}

	const T& operator*() const
	{
		return *m_data;
	}

	bool operator!() const
	{
		return !m_data;
	}

	bool operator<( const SharedDataPtr<T>& other ) const
	{
		return m_data < other.m_data;
	}

	bool operator==( const SharedDataPtr<T>& other ) const
	{
		return m_data == other.m_data;
	}

	bool operator!=( const SharedDataPtr<T>& other ) const
	{
		return m_data != other.m_data;
	}

	SharedDataPtr( const SharedDataPtr<T>& other ) : m_data( other.m_data )
	{
		incref( m_data );
	}

	SharedDataPtr<T>& operator=( const SharedDataPtr<T>& other )
	{
		if( m_data != other.m_data )
		{
			T* temp = m_data;
			m_data = other.m_data;
			incref( m_data );
			decref( temp );
		}
		return *this;
	}

	SharedDataPtr<T>& operator=( T* other )
	{
		if( m_data != other )
		{
			T* temp = m_data;
			m_data = other;
			incref( m_data );
			decref( temp );
		}
		return *this;
	}

private:

	static void incref( T* data )
	{
		if( data )
			++data->m_refcount;
	}

	static void decref( T* data )
	{
		if( data && --data->m_refcount == 0 )
			delete data;
	}

	T* m_data;
};

} // namespace kiwi
