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

  File:		YEventFilter.h

  Author:	Stefan Hundhammer <sh@suse.de>

/-*/

#ifndef YEventFilter_h
#define YEventFilter_h


#include "ImplPtr.h"


class YEvent;
class YDialog;

class YEventFilterPrivate;


/**
 * Abstract base class to filter events.
 *
 * This class can be used to examine events just before they are delivered to
 * the application. This is most useful for higher-level widgets or for
 * libraries that need to react to certain events and either consume them, have
 * them delivered unchanged to the application, or exchange an event with
 * another one.
 *
 * A YEventFilter belongs to one specific dialog. Each dialog can have any
 * number of event filters. Each of those event filters is called (its
 * YEventFilter::filter() method) for each event inside
 * YDialog::waitForEvent(). The order in which event filters are called is
 * undefined.
 *
 * YEventFilter objects should be created with 'new' (on the heap). Since an
 * YEventFilter registers itself with its dialog, the dialog will delete it in
 * its destructor if it still exists after all child widgets are deleted.
 *
 * Thus, it is safe to store a pointer to an YEventFilter until the
 * corresponding dialog is deleted. After that, the pointer becomes invalid.
 *
 * See YHelpButtonHandler in YDialog.cc for an example.
 **/
class YEventFilter
{
protected:
    /**
     * Constructor.
     *
     * This registers the event filter with the specified dialog. The dialog
     * assumes ownership of this object and will delete it in its destructor
     * (unless this object is destroyed before that time).
     *
     * If 'dialog' is 0, YDialog::currentDialog() is used (which can throw a
     * YUINoDialogException if there is no dialog).
     **/
    YEventFilter( YDialog * dialog = 0 );

public:
    /**
     * Destructor.
     *
     * This will unregister this object with its dialog.
     **/
    virtual ~YEventFilter();

    /**
     * The heart of the matter: The event filter function.
     * Derived classes are required to implement this.
     *
     * This method can inspect the event it receives.  Hint: event->widget()
     * is typically the most interesting information.
     *
     * This method can react on individual events and
     *
     *   - consume the event (i.e., return 0)
     *   - pass the event through unchanged (simply return the event)
     *   - create a new event (typically based on data in the received event).
     *
     * If 0 or a new event (another value than 'event') is returned, the old
     * event is deleted. If a value different from 'event' or 0 is returned,
     * that value is assumed to be a pointer to a newly created event. The
     * dialog will assume ownership of that event and delete it when
     * appropriate.
     *
     * Note: Never delete 'event' in this method! Return 0 or a new event
     * instead; the caller will take care of deleting the old event.
     **/
    virtual YEvent * filter( YEvent * event ) = 0;

    /**
     * Return the dialog this event filter belongs to.
     **/
    YDialog * dialog() const;

private:

    ImplPtr<YEventFilterPrivate> priv;
};


#endif // YEventFilter_h
