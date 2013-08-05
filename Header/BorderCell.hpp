//File: BorderCell.hpp
//Author:   John Miner
//Creted:   03/26/12
//Modified: 03/26/12
//Purpose:  A value constraining class for communicating between BorderLayout
//          and users about certain areas of the layout
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License
/*
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
SUCH DAMAGES.
*/

#ifndef BORDER_CELL_HPP_
#define BORDER_CELL_HPP_

//! Constrain values when talking with BorderLayout
/*!
    A value constraining class for communicating between BorderLayout
    and the users of the class. This is essentially a constant representing
    a certain cell of the BorderLayout.
*/
class BorderCell
{
public:
    //! Copy ctor.
    BorderCell(const BorderCell &rhs);
    //! Copy assignment.
    BorderCell &operator=(const BorderCell &rhs);
    //! dtor.
    ~BorderCell();
    //! No BorderLayout cell.
    /*!
        Essentially a constant representing no BorderLayout cell.
        Not the actual cell, but but used as a value constraining parameter.
    */
    static BorderCell None();
    //! Top BorderLayout cell.
    /*!
        Essentially a constant representing top BorderLayout cell.
        Not the actual cell, but but used as a value constraining parameter.
    */
    static BorderCell Top();
    //! Left BorderLayout cell.
    /*!
        Essentially a constant representing left BorderLayout cell.
        Not the actual cell, but but used as a value constraining parameter.
    */
    static BorderCell Left();
    //! Right BorderLayout cell.
    /*!
        Essentially a constant representing right BorderLayout cell.
        Not the actual cell, but but used as a value constraining parameter.
    */
    static BorderCell Right();
    //! Bottom BorderLayout cell.
    /*!
        Essentially a constant representing bottom BorderLayout cell.
        Not the actual cell, but but used as a value constraining parameter.
    */
    static BorderCell Bottom();
    //! Center BorderLayout cell.
    /*!
        Essentially a constant representing center BorderLayout cell.
        Not the actual cell, but but used as a value constraining parameter.
    */
    static BorderCell Center();
    //!< operator
    /*!
        \param rhs the right operand.

        Used so STL sorting algorithm can be used when objects of this class
        are stored in an STL container. Order of objects is somewhat arbitrary.
    */
    bool operator<(const BorderCell &rhs) const;
    //!!= operator
    /*!
        \param rhs the right operand.

        Checks for inequality.
    */
    bool operator!=(const BorderCell &rhs) const;
    //!== operator
    /*!
        \param rhs the right operand.

        Checks for equality.
    */
    bool operator==(const BorderCell &rhs) const;
protected:
    //! Initialize class.
    /*!
        \param value what to assign to member value

        Called by ctors and copy assignment operator
        Initialize class
        Note: This is going to be removed and replaced by the ctor's
        initialization list.
    */
    void initialize(int value);
    //! Free memory and destruct.
    /*! 
        Called by dtor and copy assignment operator to free memory, destruct
        Note: This is going to be removed and put into body of dtor and
        copy assignment operator.
    */
    void dispose();
private:
    //! Default ctor.
    /*!
        Private so instances of this class cannot be created besides None,
        Top, Bottom, Left, Right, Center.
    */
    BorderCell();
    //! ctor
    /*! 
        \param value what to assign to member value.

        Set the member value to param value.
    */
    BorderCell(int value);
    //! Internal representation of None, Top, Bottom, Left, Right, Center
    /*!
        An integer representation of allowed values to pass to BorderLayout
        methods. Can represent the following cells: None, Top, Bottom, Left,
        Right, Center.
    */
    int value;
};

#endif

