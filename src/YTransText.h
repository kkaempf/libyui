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

  File:		YTransText.h

  Author:	Stefan Hundhammer <sh@suse.de>

/-*/

#ifndef YTransText_h
#define YTransText_h

#include <libintl.h>
#include <string>


/**
 * Helper class for translated strings: Stores a message in the original
 * (untranslated) version along with the translation into the current locale.
 **/
class YTransText
{
public:

    /**
     * Constructor with both original and translated message.
     **/
    YTransText( const std::string & orig,
		const std::string & translation )
	: _orig( orig ), _translation( translation ) {}

    /**
     * Constructor that automatically translates the original message.
     **/
    YTransText( const std::string & orig ) : _orig( orig )
    {
	_translation = gettext( _orig.c_str() );
    }

    /**
     * Copy constructor.
     **/
    YTransText( const YTransText & src )
    {
	_orig		= src.orig();
	_translation	= src.translation();
    }

    /**
     * Assignment operator.
     **/
    YTransText & operator= ( const YTransText & src )
    {
	_orig		= src.orig();
	_translation	= src.translation();

	return *this;
    }

    /**
     * Return the original message.
     **/
    const std::string & orig()		const { return _orig;		}

    /**
     * Return the translation.
     **/
    const std::string & translation()	const { return _translation;	}

    /**
     * Return the translation.
     * ( alias, just as a shortcut )
     **/
    const std::string & trans()		const { return _translation;	}

    /**
     * Set the original message. Does not touch the translation, so make sure
     * you change both if you want to keep them synchronized!
     **/
    void setOrig( const std::string & newOrig ) { _orig = newOrig; }

    /**
     * Set the translation.
     **/
    void setTranslation( const std::string & newTrans ) { _translation = newTrans; }

    /**
     * operator< : Compares translations.
     **/
    bool operator< ( const YTransText & other ) const
	{ return _translation < other.translation(); }

    /**
     * operator> : Compares translations.
     **/
    bool operator> ( const YTransText & other ) const
	{ return _translation > other.translation(); }

    /**
     * operator== : Compares translations.
     **/
    bool operator== ( const YTransText & other ) const
	{ return _translation == other.translation(); }


private:

    std::string	_orig;
    std::string	_translation;

};



#endif // YTransText_h
