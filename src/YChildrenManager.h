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

  File:		YChildrenManager.h

  Author:	Stefan Hundhammer <sh@suse.de>

/-*/

#ifndef YChildrenManager_h
#define YChildrenManager_h

#include <list>
#include <algorithm>
#include <YUIException.h>


/**
 * Abstract base template class for children management, such as child
 * widgets.
 **/
template<class T> class YChildrenManager
{
public:

    /**
     * Constructor.
     *
     * 'containerParent' is the class whose children are managed.
     **/
    YChildrenManager( T * containerParent )
	: _container( containerParent )
	{}

    /**
     * Destructor.
     **/
    virtual ~YChildrenManager() {}


    typedef std::list<T *> ChildrenList;

    /**
     * Check if there are any children.
     **/
    bool hasChildren() const { return ! empty(); }

    /**
     * Check if the children list is empty, i.e. if there are no children.
     **/
    bool empty() const { return _children.empty(); }

    /**
     * Returns the number of children.
     **/
    int	count() const { return _children.size(); }

    /**
     * Return an iterator that points to the first child.
     **/
    typename ChildrenList::const_iterator begin() const
	{ return _children.begin(); }

    /**
     * Return an iterator that points after the last child.
     **/
    typename ChildrenList::const_iterator end() const
	{ return _children.end(); }

    /**
     * Return a reverse iterator that points to the last child.
     **/
    typename ChildrenList::const_reverse_iterator rbegin() const
	{ return _children.rbegin(); }

    /**
     * Return a reverse iterator that points before the first child.
     **/
    typename ChildrenList::const_reverse_iterator rend() const
	{ return _children.rend(); }

    /**
     * Returns the first child or 0 if there is none.
     * Useful mostly for children managers that handle only one child.
     **/
    T * firstChild()
	{ return _children.empty() ? (T *) 0 : _children.front(); }

    /**
     * Returns the last child or 0 if there is none.
     **/
    T * lastChild()
	{ return _children.empty() ? (T *) 0 : _children.back(); }

    /**
     * Add a new child.
     *
     * This may throw exceptions if more children are added than the class
     * whose children are handled (the associated widget) can handle.
     **/
    virtual void add( T * child )
	{ _children.push_back( child ); }

    /**
     * Remove a child. This only removes the child from the children manager's
     * list; it does not delete it.
     **/
    virtual void remove( T * child )
	{ _children.remove( child ); }

    /**
     * Remove all children. This only removes the children from the children
     * manager's list; it does not delete them.
     **/
    virtual void clear()
	{ _children.clear(); }

    /**
     * Check if the children list contains the specified child.
     * Returns 'true' if the children list contains the child,
     * 'false' otherwise.
     **/
    bool contains( T * child ) const
    {
	return ( find( _children.begin(), _children.end(), child )
		 != _children.end() );
    }

    /**
     * Returns the associated container, i.e. the object whose children are
     * handled here.
     **/
    T * container() const { return _container; }

protected:

    T *			_container;
    ChildrenList 	_children;
};


/**
 * Children manager that can handle one single child (rejecting any more).
 * Useful for YAlignment, YFrame etc.
 **/
template<class T> class YSingleChildManager: public YChildrenManager<T>
{
public:

    YSingleChildManager( T * containerParent )
	: YChildrenManager<T>( containerParent )
	{}

    /**
     * Add a new child.
     *
     * Reimplemented from YChildrenManager.
     *
     * This will throw a YUITooManyChildrenException if there already is a
     * child.
     **/
    virtual void add( T * child )
    {
	if ( this->empty() )
	    this->_children.push_back( child );
	else
	    YUI_THROW( YUITooManyChildrenException<T>( this->container() ) );
    }

    /**
     * Replace the previous child (if any) with a new one.
     **/
    void replace( T * newChild )
    {
	this->_children.clear();
	this->_children.push_back( newChild );
    }
};


/**
 * Children manager that rejects all children.
 *
 * Useful for widget classes that can't handle children such as YPushButton,
 * YSelectionBox etc.
 **/
template<class T> class YChildrenRejector: public YChildrenManager<T>
{
public:
    /**
     * Constructor.
     **/
    YChildrenRejector( T * containerParent )
	: YChildrenManager<T>( containerParent )
	{}

    /**
     * Add a new child.
     *
     * Reimplemented from YChildrenManager.
     *
     * Since this class is designed to reject children, this always throws a
     * YUITooManyChildrenException.
     **/
    virtual void add( T * child )
	{ YUI_THROW( YUITooManyChildrenException<T>( this->container() ) ); }
};


#endif // YChildrenManager_h
