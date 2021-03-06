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

  File:       FSize.cc

  Author:     Michael Andres <ma@suse.de>
  Maintainer: Michael Andres <ma@suse.de>

  Purpose:

/-*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "FSize.h"

using namespace std;

FSize::FSize( const string &sizeStr, const Unit unit_r )
  : _size( atoll( sizeStr.c_str() ) * factor( unit_r ) )
{
}

///////////////////////////////////////////////////////////////////
//
//
//	METHOD NAME : FSize::fillBlock
//	METHOD TYPE : FSize &
//
//	DESCRIPTION :
//
FSize & FSize::fillBlock( FSize blocksize_r )
{
  if ( _size && blocksize_r ) {
    long long diff = _size % blocksize_r;
    if ( diff ) {
      if ( _size > 0 )
	_size += blocksize_r;
      _size -= diff;
    }
  }
  return *this;
}

///////////////////////////////////////////////////////////////////
//
//
//	METHOD NAME : FSize::bestUnit
//	METHOD TYPE : FSize::Unit
//
//	DESCRIPTION :
//
FSize::Unit FSize::bestUnit() const
{
  long long usize( _size < 0 ? -_size : _size );
  if ( usize < KB )
    return B;
  if ( usize < MB )
    return K;
  if ( usize < GB )
    return M;
  if ( usize < TB )
    return G;
  return T;
}

///////////////////////////////////////////////////////////////////
//
//
//	METHOD NAME : FSize::form
//	METHOD TYPE : std::string
//
//	DESCRIPTION :
//
std::string FSize::form( const Unit unit_r, unsigned fw, unsigned prec, const bool showunit ) const
{
  if ( prec == bestPrec ) {
    switch ( unit_r )
    {
      case T:  prec = 3; break;
      case G:  prec = 2; break;
      case M:  prec = 1; break;
      case K:  prec = 1; break;
      case B:  prec = 0; break;
    }
  } else if ( unit_r == B )
    prec = 0; // doesn't make sense for Byte

  char buffer[80]; // should be long enough for any numeric sprintf()
  snprintf( buffer, sizeof( buffer ),
	    "%*.*f",
	    fw, prec, ( double( _size ) / factor( unit_r ) ) );

  string ret( buffer );

  if ( showunit )
    ret += string(" ") + unit( unit_r );

  return ret;
}


///////////////////////////////////////////////////////////////////
//
//
//	METHOD NAME : FSize::asString
//	METHOD TYPE : std::string
//
//	DESCRIPTION :
//
std::string FSize::asString() const
{
  return form();
}
