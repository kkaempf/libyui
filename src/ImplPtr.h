/*************************************************************************************************************

 Copyright (C) 2000 - 2010 Novell, Inc.   All Rights Reserved.

 This program is free software; you can redistribute it and/or modify it under the terms of the GNU General
 Public License as published by the Free Software Foundation; either version 2 of the License, or (at your
 option) any later version.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
 implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 for more details.

 You should have received a copy of the GNU General Public License along with this program; if not, write to
 the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*************************************************************************************************************/



 /////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////
 ////                                                                                                     ////
 ////                                                                                                     ////
 ////                                                                                                     ////
 ////   __/\\\\\\_____________/\\\__________/\\\________/\\\___/\\\________/\\\___/\\\\\\\\\\\_           ////
 ////    _\////\\\____________\/\\\_________\///\\\____/\\\/___\/\\\_______\/\\\__\/////\\\///__          ////
 ////     ____\/\\\______/\\\__\/\\\___________\///\\\/\\\/_____\/\\\_______\/\\\______\/\\\_____         ////
 ////      ____\/\\\_____\///___\/\\\_____________\///\\\/_______\/\\\_______\/\\\______\/\\\_____        ////
 ////       ____\/\\\______/\\\__\/\\\\\\\\\_________\/\\\________\/\\\_______\/\\\______\/\\\_____       ////
 ////        ____\/\\\_____\/\\\__\/\\\////\\\________\/\\\________\/\\\_______\/\\\______\/\\\_____      ////
 ////         ____\/\\\_____\/\\\__\/\\\__\/\\\________\/\\\________\//\\\______/\\\_______\/\\\_____     ////
 ////          __/\\\\\\\\\__\/\\\__\/\\\\\\\\\_________\/\\\_________\///\\\\\\\\\/_____/\\\\\\\\\\\_    ////
 ////           _\/////////___\///___\/////////__________\///____________\/////////______\///////////__   ////
 ////                                                                                                     ////
 ////                                                                                                     ////
 ////                 widget abstraction library providing Qt, GTK and ncurses frontends                  ////
 ////                                                                                                     ////
 ////                                   3 UIs for the price of one code                                   ////
 ////                                                                                                     ////
 ////                                       ***  core library  ***                                        ////
 ////                                                                                                     ////
 ////                                                                                                     ////
 ////                                                                                                     ////
 ////                                                                              (C) SUSE Linux GmbH    ////
 ////                                                                                                     ////
 ////                                                              libYUI-AsciiArt (C) 2012 Björn Esser   ////
 ////                                                                                                     ////
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*-/

  File:	      ImplPtr.h

  Author:     Michael Andres <ma@suse.de>

/-*/

#ifndef ImplPtr_h
#define ImplPtr_h

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

/**
 * Helper template class for implementation pointers (pointers to a private
 * class or structure that hold the member variables of a higher-level class
 * that is part of a public API).
 *
 * This pointer class maintains constness of its parent class, i.e. if it is
 * used in a const class the class this pointer points to will also be const.
 *
 * This class automatically deletes the class it points to in its destructor.
 **/
template<class _Impl>
class ImplPtr : private boost::noncopyable
{
    typedef typename boost::scoped_ptr<_Impl>::unspecified_bool_type unspecified_bool_type;

public:
    typedef _Impl element_type;

    explicit
    ImplPtr( _Impl * impl_r = 0 )    : _impl( impl_r ) {}

public:
    void reset( _Impl * impl_r = 0 ) { _impl.reset( impl_r ); }

    void swap( ImplPtr rhs )         { _impl.swap( rhs._impl ); }

public:
    operator unspecified_bool_type() const { return _impl; }

    const _Impl & operator*()  const { return *_impl; }
    const _Impl * operator->() const { return _impl.get(); }
    const _Impl * get()        const { return _impl.get(); }

    _Impl &       operator*()        { return *_impl; }
    _Impl *       operator->()       { return _impl.get(); }
    _Impl *       get()              { return _impl.get(); }

private:
    boost::scoped_ptr<_Impl> _impl;
};

template<class _Impl>
inline bool operator==( ImplPtr<_Impl> & lhs, ImplPtr<_Impl> & rhs ) { return lhs.get() == rhs.get(); }

template<class _Impl>
inline bool operator!=( ImplPtr<_Impl> & lhs, ImplPtr<_Impl> & rhs ) { return lhs.get() != rhs.get(); }

template<class _Impl>
inline bool operator< ( ImplPtr<_Impl> & lhs, ImplPtr<_Impl> & rhs ) { return lhs.get() <  rhs.get(); }

#endif // ImplPtr_h
