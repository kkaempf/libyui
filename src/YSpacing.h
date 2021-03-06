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

  File:		YSpacing.h

  Author:	Stefan Hundhammer <sh@suse.de>

/-*/

#ifndef YSpacing_h
#define YSpacing_h

#include "YWidget.h"
#include "ImplPtr.h"

class YSpacingPrivate;


/**
 * HSpacing, VSpacing, HStretch, VStretch
 **/
class YSpacing: public YWidget
{
public:

    /**
     * Constructor.
     *
     * A Spacing/Stretch widget works only in one dimension ('dim') at the same
     * time. But it can be stretchable and have a size at the same time, in
     * which case the specified size acts very much like a minimal size - but
     * not exactly, since YLayoutBox will reduce Spacings first before other
     * widgets have to be resized below their preferred size.
     *
     * 'layoutUnits' is specified in abstract UI units where a main window
     * (800x600 pixels in the Qt UI) corresponds to a 80x25 window.
     **/
    YSpacing( YWidget *		parent,
	      YUIDimension 	dim,
	      bool 		stretchable	= false,
	      YLayoutSize_t 	layoutUnits	= 0.0 );

    /**
     * Destructor.
     **/
    virtual ~YSpacing();

    /**
     * Return a descriptive name of this widget class for logging,
     * debugging etc.
     **/
    virtual const char * widgetClass() const;

    /**
     * Return the primary dimension of this Spacing/Stretch,
     * i.e. the dimension in which it uses space or stretches.
     **/
    YUIDimension dimension() const;

    /**
     * Return the size in the primary dimension.
     *
     * This is the device dependent size (pixels or character cells), not the
     * abstract UI layout unit from the constructor.
     **/
    int size() const;

    /**
     * Return the size in the specified dimension.
     *
     * This is the device dependent size (pixels or character cells), not the
     * abstract UI layout unit from the constructor.
     **/
    int size( YUIDimension dim ) const;

    /**
     * Preferred width of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual int preferredWidth();

    /**
     * Preferred height of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual int preferredHeight();


private:

    ImplPtr<YSpacingPrivate> priv;
};


typedef YSpacing YVSpacing;
typedef YSpacing YHSpacing;
typedef YSpacing YHStretch;
typedef YSpacing YVStretch;


#endif // YSpacing_h
