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

  File:		YShortcutManager.h

  Author:	Stefan Hundhammer <sh@suse.de>

/-*/


#ifndef YShortcutManager_h
#define YShortcutManager_h

#include "YWidget.h"
#include "YShortcut.h"

class YDialog;

/**
 * Helper class to manage keyboard shortcuts within one dialog and resolve
 * keyboard shortcut conflicts.
 **/
class YShortcutManager
{
public:
    /**
     * Constructor.
     **/
    YShortcutManager( YDialog *dialog );

    /**
     * Destructor
     **/
    virtual ~YShortcutManager();

    /**
     * Check the keyboard shortcuts of all children of this dialog
     * (not for sub-dialogs!).
     *
     * Call resolveAllConflicts() if 'autoResolve' is 'true'.
     **/
    void checkShortcuts( bool autoResolve = true );

    /**
     * Returns the number of shortcut conflicts.
     * Valid only after checkShortcuts() or resolveAllConflicts().
     **/
    int conflictCount() { return _conflictCount; }

    /**
     * Resolve shortcut conflicts. Requires checkShortcuts() to be called first.
     *
     * Note: This may or may not work. There is no general solution to that
     * problem. This method tries its best, but you may end up with widgets
     * that don't have any ( more ) shortcut.
     *
     * Why? Just picture the following ( admittedly pathologic ) situation:
     *
     * [& OK]
     * [& OK]
     * [& OK]
     *
     * This will result in something like this:
     *
     * [& OK]
     * [O& K]
     * [OK]
     *
     * I.e. the first OK button will retain its preferred shortcut ( 'O' ), the
     * second OK button's shortcut will be reassigned to 'K' and the third
     * won't get any - there are simply not enough eligible shortcut
     * characters.
     *
     * This may even fail in much less pathological situations. This example is
     * only supposed to give you a general idea why not to blindly rely on
     * automatic shortcut resolving.
     *
     * It's always best to resolve conflicts manually. This will generally
     * result in much better shortcuts: Easier to memorize, less chance of
     * picking characters that cannot really do a good job showing their
     * shortcut like very narrow characters ( .e.g., 'i' ) or descender
     * characters ( e.g., 'g', 'p', 'q' - imagine those underlined! ).
     **/
    void resolveAllConflicts();

    /**
     * Returns the dialog this shortcut manager works on.
     **/
    YDialog *dialog() { return _dialog; }

protected:

    /**
     * Delete all members of the internal shortcut list, then empty the list.
     **/
    void clearShortcutList();

    /**
     * Recursively search all widgets between iterators 'begin' and 'end' (not
     * those of any sub-dialogs!) for child widgets that could accept a
     * keyboard shortcut and add these to _shortcutList.
     **/
    void findShortcutWidgets( YWidgetListConstIterator begin,
			      YWidgetListConstIterator end );

    /**
     * Pick a new shortcut character for 'shortcut' - one that isn't marked as
     * used in the '_used' array. Unset the conflict marker if that succeeded.
     **/
    void resolveConflict( YShortcut * shortcut );

    /**
     * Find the shortest wizard button in 'conflictList', if there is any.
     * Returns the index of that shortest wizard button or -1 if there is none.
     **/
    int findShortestWizardButton( const YShortcutList & conflictList );

    /**
     * Find the shortest widget in 'conflictList'. Buttons get priority if they
     * have the same number of eligible shortcut characters as another widget.
     *
     * Returns the index of the shortest widget.
     **/
    unsigned findShortestWidget( const YShortcutList & conflictList );

    /**
     * The dialog this shortcut manager works on.
     **/
    YDialog *_dialog;

    /**
     * List of all the shortcuts in this dialog.
     **/
    YShortcutList _shortcutList;

    /**
     * Counters for wanted shortcut characters.
     **/
    int _wanted[ sizeof( char ) << 8 ];


    /**
     * Flags for used shortcut characters.
     **/
    bool _used[ sizeof( char ) << 8 ];


    /**
     * Counter for shortcut conflicts
     **/
    int _conflictCount;


private:

    bool _didCheck;
};


#endif // YShortcutManager_h
