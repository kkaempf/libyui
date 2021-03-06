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

  File:		YBothDim.h

  Author:	Stefan Hundhammer <sh@suse.de>

/-*/

#ifndef YBothDim_h
#define YBothDim_h

#include "YTypes.h"
#include "YUIException.h"


/**
 * Template class for two-dimensional entities, such as
 * - width, height
 * - x_pos, y_pos
 * - hStretchable, vStretchable
 *
 * Precondition: type T needs to have a default constructor
 * (which all simple types like int, long, bool have).
 **/
template<typename T> class YBothDim
{
public:

    // Data Members - intentionally public
    T vert;
    T hor;

    /**
     * Constructor with explicit initialization for both values
     **/
    YBothDim( T hor, T vert )
	: vert( vert )
	, hor( hor )
	{}

    /**
     * Default constructor (calls T default constructor for both values)
     **/
    YBothDim()
	{}

    /**
     * operator[] for alternative access via  myVar[ YD_HORIZ ]
     * Please note that this returns a non-const reference, so this can be used
     * as an lvalue (e.g., in assignments)
     **/
    T & operator[]( YUIDimension dim )
    {
	switch ( dim )
	{
	    case YD_HORIZ:	return hor;
	    case YD_VERT:	return vert;
	    default:		YUI_THROW( YUIInvalidDimensionException() );
	}

	// never reached (but gcc will complain otherwise)
	return hor;
    }

    /**
     * Same as above for const objects
     **/
    const T & operator[]( YUIDimension dim ) const
    {
	switch ( dim )
	{
	    case YD_HORIZ:	return hor;
	    case YD_VERT:	return vert;
	    default:		YUI_THROW( YUIInvalidDimensionException() );
	}

	// never reached (but gcc will complain otherwise)
	return hor;
    }
};


#endif // YBothDim_h
