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

  File:		YEmpty.cc

  Author:	Stefan Hundhammer <sh@suse.de>

/-*/


#include "YSpacing.h"
#include "YUI.h"
#include "YApplication.h"


struct YSpacingPrivate
{
    YSpacingPrivate( YUIDimension dim, int size )
	: dim( dim )
	, size( size )
	{}

    YUIDimension	dim;
    int			size;
};




YSpacing::YSpacing( YWidget * parent, YUIDimension dim, bool stretchable, YLayoutSize_t layoutUnits )
    : YWidget( parent )
    , priv( new YSpacingPrivate( dim, YUI::app()->deviceUnits( dim, layoutUnits ) ) )
{
    YUI_CHECK_NEW( priv );
    setStretchable( dim, stretchable );
    setStretchable( dim == YD_HORIZ ? YD_VERT : YD_HORIZ, false );
}


YSpacing::~YSpacing()
{
    // NOP
}


YUIDimension
YSpacing::dimension() const
{
    return priv->dim;
}


int YSpacing::size() const
{
    return priv->size;
}


int YSpacing::size( YUIDimension dim ) const
{
    if ( dim == priv->dim )	return priv->size;
    else			return 0;
}


int YSpacing::preferredWidth()
{
    if ( priv->dim == YD_HORIZ )
	return priv->size;
    else
	return 0;
}


int YSpacing::preferredHeight()
{
    if ( priv->dim == YD_VERT )
	return priv->size;
    else
	return 0;
}


const char *
YSpacing::widgetClass() const
{
    if ( priv->size > 0 )
	return ( priv->dim == YD_HORIZ ) ? "YHSpacing" : "YVSpacing";

    if ( stretchable( YD_HORIZ ) )	return "YHStretch";
    if ( stretchable( YD_VERT  ) )	return "YVStretch";

    return "YSpacing";
}
