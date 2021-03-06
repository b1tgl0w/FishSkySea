//File: ClipFit.cpp
//Author:   John Miner
//Created:  02/28/12
//Modified: 02/28/12
//Purpose:  Class that will clip images that do not fit within a layout
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

#include "../Header/ClipFit.hpp"

ClipFit::ClipFit()
{
}

ClipFit::ClipFit(const ClipFit &rhs)
{
}

ClipFit &ClipFit::operator=(const ClipFit &rhs)
{
    if( &rhs == this )
        return *this;

    return *this;
}

ClipFit::~ClipFit()
{
}

void ClipFit::initialize()
{
}

void ClipFit::dispose()
{
    //No-op
}

//Method:   fit(...)
//Purpose:  Clip all images that do not fit within a layout
//Note: Does not use position or size parameters
void ClipFit::fit(std::list<boost::shared_ptr<RendererElement> > 
    &rendererElements, const Point &position, const Dimension &size,
    boost::shared_ptr<Clip> &clipObject)
{
    std::list<boost::shared_ptr<RendererElement> > rendererElementsCopy =
        rendererElements;

    for( std::list<boost::shared_ptr<RendererElement> >::iterator it =
        rendererElementsCopy.begin(); it != rendererElementsCopy.end(); ++it )
        (*it)->clip(clipObject);
}

