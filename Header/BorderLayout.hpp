//File: BoarderLayout.hpp
//Author:   John Miner
//Created:  03/26/12
//Modified: 03/26/12
//Purpose:  Arrange the "Parent" layout into borders.
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

#ifndef BORDER_LAYOUT_HPP_
#define BORDER_LAYOUT_HPP_

#include <list>
#include <map>
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "Layout.hpp"
#include "BorderSize.hpp"
#include "BorderCorner.hpp"
#include "BorderCell.hpp"
#include "RendererElement.hpp"
#include "Dimension.hpp"
#include "DimensionPercent.hpp"
#include "Point.hpp"
#include "EmptyLayout.hpp"

//! Make a border around the screen and put sublayouts there
/*! Make a border that is divided up into the following sections: Top, Left,
    Right, Bottom, Center. Put sublayouts into one of those sections. This 
    border layout can, itself, be a sublayout. In that case, the border won't
    be around the entire screen, but around a cell of another layout. Not
    all cells must contain sublayouts. Border size can be Thin, Medium, or
    Thick.
*/
class BorderLayout : public Layout,
    public boost::enable_shared_from_this<BorderLayout>
{
public:
    //! ctor
    /*!
        \param borderSize The thickness of the borders. (Thin, Medium, or Thick).

        Create a new border layout with borders of the appropriate size.
    */
    BorderLayout(const BorderSize &borderSize);
    //! Copy ctor.
    BorderLayout(const BorderLayout &rhs);
    //! Copy assignment.
    BorderLayout &operator=(const BorderLayout &rhs);
    //! dtor.
    ~BorderLayout();
    //! Asks sublayouts for REs and passes them to parent layout
    /*!
        Asks all sublayouts for their RendererElements, and after collecting all
        of them, passes the entire collection to its parent layout.
    */
    void render();
    //! No-op
    /*!
        No-op because non-ptr RendererElements can't be added to this layout.
        Inherited pure virtual method. 
    */
    void drawWhenReady(RendererElement &re);
    //! Add a RendererElement to be drawn next frame.
    /*!
        \param re The RendererElement to be drawn.

        \param callerLayout Not used.

        Add a renderer element to collection of elements to be drawn next frame.
    */
    void drawWhenReady(boost::shared_ptr<RendererElement> &re,
        boost::shared_ptr<Layout> &callerLayout);
    //! Add a list of RendererElements to be drawn next frame.
    /*!
        \param toDraw List of RendererElements to be drawn in addition to other REs.

        \param callerLayout Not used.

        Add a list of RendererElements to be drawn next frame. The list is
        merged with the existing list of other RendererElements to be drawn.
    */
    void drawWhenReady(const std::list<boost::shared_ptr<RendererElement> > &toDraw,
        boost::shared_ptr<Layout> &callerLayout);
    //! Resize the BorderLayout and cells
    /*!
        \param size The new width and height of the BorderLayout

        Change the size of this BorderLayout and resize and reposition each
        cell.
    */
    void scale(const Dimension &size);
    //! Resize the BorderLayout and cells
    /*!
        \param dimensionPercent Percentage of the current size used to calc new size.

        Change the size of this BorderLayout and resize and reposition each
        cell. dimensionPercent is multiplied by the current width and height.
    */
    void scale(const DimensionPercent &dimensionPercent);
    //! Move this BorderLayout 
    /*!
        \param newPosition Where to move the BorderLayout.

        Move this BorderLayout from its current position and resize and move 
        each cell.
    */
    void moveTo(const Point &newPosition);
    //! Move this border layout
    /*!
        \param newPosition Add this point to current position to get final position.

        Move this BorderLayout from its current position. Add the current
        position to newPosition to get the final position.
    */
    void moveBy(const Point &newPosition);
    //! Is the BorderLayout located at this position?
    /*!
        \param position Is the BorderLayout located at this location?

        Tell caller layout whether the BorderLayout is at the position given.
    */
    bool isHere(const Point &position);
    //! Add sublayout to a cell
    /*!
        \param layout sublayout to be added to cell.
        
        \param whichCell which cell to add the sublayout to.

        Add sublayout to a specific cell and move and position it accordingly.
    */
    void addLayout(boost::shared_ptr<Layout> &layout, const BorderCell
        &whichCell);
    void removeLayout(boost::shared_ptr<Layout> &layout, const BorderCell &
        whichCell);
    //! Provide access to contained layouts
    /*!
        \param whichCell The cell to work on. Either Top, Bottom, Left, Right, Center.

        Provide access to contained layouts.
    */
    boost::weak_ptr<Layout> getElement(const BorderCell &whichCell);
    //! Allow sides or Top/Bottom to use corners.
    /*!
        \param borderCorner which sides should make use of the corners. Sides, TopBottom, None.

        Allow sides or top/bottom to extend their layouts into the corners. The
        corners are where two cells overlap.
    */
    void useCorners(const BorderCorner &borderCorner);
    //! Register the parent layout of this class
    /*!
        \param owner The parent layout.

        Register the parent layout of this class.
    */
    void own(const boost::weak_ptr<Layout> &owner);
protected:
    //! Initialize object.
    /*!
        \param borderSize The thickness of the border cells.

        Called by ctors and copy assignment operator to initialize class.
        Essentially factoring out common code.
        Note: this is going to be removed and replaced by the ctor's
        initialization list.
    */
    void initialize(const BorderSize &borderSize);
    //! Free memory and destruct.
    /*!
        Called by dtor and copy assignment operator to free memory and destruct.
        Note: This is going to be removed and put into body of dtor and
        copy assignment operator.
    */
    void dispose();
private:
    //! Default ctor. Private.
    /*!
        Default ctor is private so BorderLayouts aren't created without providing
        a thickness for cells.
    */
    BorderLayout();
    //! Move and position all cells
    /*!
        Move and position all cells by calling overloaded adjustCell(...)
        on each individual cell.
    */
    void adjustCells();
    //! Resize and reposition cell
    /*!
        \param whichCell The cell to work on. Either Top, Bottom, Left, Right, Center.

        Resize and reposition a certain cell and also the sublayouts of that
        cell.
    */
    void adjustCell(const BorderCell &whichCell);
    //! List of RendererElements to be drawn next frame.
    /*!
        List of RendererElements to be drawn next frame. Cleared after sent
        to parent layout.
    */
    std::list<boost::shared_ptr<RendererElement> > toDraw;
    //! Sublayouts.
    /*!
        Sublayouts in the Top, Bottom, Left, Right, and Center cells of this
        BorderLayout.
    */
    std::map<BorderCell, boost::shared_ptr<Layout> > cells;
    //! Parent layout.
    boost::weak_ptr<Layout> owner;
    //! Relative position to parent layout's position.
    Point position;
    //! Size of layout.
    /*!
        Sizes of individual cells will be calculated.
    */
    Dimension size;
    //! Thickness of border cells.
    /*!
        Thickness of border cells. Does not directly apply to center cell, although
        the thicker the border cells are, the less available space there is
        for the center cell.
    */
    BorderSize borderSize;
    //! Which sides can use the corners
    /*!
        Specifies whehter the Sides or Top/Bottom can use corners (the space
        that overlaps cells.) Can be set to none.
    */
    BorderCorner borderCorner;
    //! No sublayout in cell.
    boost::shared_ptr<Layout> emptyLayout;
};

#endif

