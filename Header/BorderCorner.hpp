//File: BorderCorner.hpp
//Author:   John Miner
//Created:  03/26/12
//Modified: 03/26/12
//Purpose:  A value constraining class used for communicating between 
//          user and a BorderLayout in regard to which corners are used
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

#ifndef BORDER_CORNER_HPP_
#define BORDER_CORNER_HPP_

//! Constrain values when talking with BorderLayout
/*!
    A value constraining class for communicating between BorderLayout
    and the users of the class. This is essentially a constant representing
    which edges of the border can use the corners (the overlapping area of
    the cells)
*/
class BorderCorner
{
public:
    //! Copy ctor
    BorderCorner(const BorderCorner &rhs);
    //! Copy assignment
    BorderCorner &operator=(const BorderCorner &rhs);
    //! dtor
    ~BorderCorner();
    //! No BorderLayout use corners
    /*! 
        Essentially a constant representing that no edges will use the corners
        where the cells overlap. Not the acutal corners but used as a value
        constraining parameter.
    */
    static BorderCorner None();
    //! Top/Bottom BorderLayout use corners
    /*! 
        Essentially a constant representing that the Top/Bottom edges will use 
        the corners where the cells overlap. Not the acutal corners but used as 
        a value constraining parameter.
    */
    static BorderCorner TopBottom();
    static BorderCorner TopBottomCenter();
    //! Top/Bottom BorderLayout use corners
    /*! 
        Essentially a constant representing that the sides will use 
        the corners where the cells overlap. Not the acutal corners but used as 
        a value constraining parameter.
    */
    static BorderCorner Sides();
    static BorderCorner SidesCenter();
    //!< operator
    /*
        \param rhs the right operand.

        Used so STL sorting algorithm can be used when objects of this class
        are stored in an STL container. Order of objects is somewhat arbitrary.
    */
    bool operator<(const BorderCorner &rhs) const;
    //!!= operator
    /*!
        \param rhs the right operand.

        Checks for inequality
    */
    bool operator!=(const BorderCorner &rhs) const;
    //!== operator
    /*!
        \param rhs the right operand.

        Checks for equality
    */
    bool operator==(const BorderCorner &rhs) const;
protected:
    //! Initialize class.
    /*!
        \param value what to assign to member value.

        Called by ctors and copy assignment operator.
        Initialize class.
        Note: This is going to be removed and replaced by the ctor's
        initialization list.
    */
    void initialize(int value);
    //! Free memory and destruct
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
        TopBottom, or Sides.
    */
    BorderCorner();
    //! ctor.
    /*!
        \param value what to assign to member value.

        Set the member value to param value.
    */
    BorderCorner(int value);
    //! Internal representation of None, TopBottom, Sides
    /*!
        An integer representation of allowed values to bass to BorderLayout
        methods. Can represent the following edges: None, TopBottom, Sides.
    */
    int value;
};

#endif

