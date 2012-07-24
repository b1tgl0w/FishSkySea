//File: BorderCell.hpp
//Author:   John Miner
//Creted:   03/26/12
//Modified: 03/26/12
//Purpose:  A value constraining class for communicating between BorderLayout
//          and users about certain areas of the layout
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

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
        Used so STL sorting algorithm can be used when objects of this class
        are stored in an STL container. Order of objects is somewhat arbitrary.
        \param rhs the right operand.
    */
    bool operator<(const BorderCell &rhs) const;
    //!!= operator
    /*!
        Checks for inequality.
        \param rhs the right operand.
    */
    bool operator!=(const BorderCell &rhs) const;
    //!== operator
    /*!
        Checks for equality.
        \param rhs the right operand.
    */
    bool operator==(const BorderCell &rhs) const;
protected:
    //! Initialize class.
    /*!
        Called by ctors and copy assignment operator
        Initialize class
        Note: This is going to be removed and replaced by the ctor's
        initialization list.
        \param value what to assign to member value
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
        Set the member value to param value.
        \param value what to assign to member value.
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

