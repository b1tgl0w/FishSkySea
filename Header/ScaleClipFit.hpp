//File: ScaleClipFit.hpp
//Author:   John Miner
//Created:  02/27/12
//Modified: 02/27/12
//Purpose:  One specific strategy for fitting a list of RendererElements in
//          a layout, scaling and clipping them to fit.
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

#ifndef SCALE_CLIP_FIT_HPP_
#define SCALE_CLIP_FIT_HPP_

#include <list>
#include "boost/shared_ptr.hpp"
#include "FitStrategy.hpp"
#include "RendererElement.hpp"
#include "Dimension.hpp"
#include "FrameCleanupSubscriber.hpp"
#include "Clip.hpp"

class ScaleClipFit : public FitStrategy
{
public:
    ScaleClipFit();
    ScaleClipFit(const ScaleClipFit &rhs);
    ScaleClipFit &operator=(const ScaleClipFit &rhs);
    ~ScaleClipFit();
    void fit(std::list<boost::shared_ptr<RendererElement> > &rendererElements,
        const Point &position, const Dimension &size,
        boost::shared_ptr<Clip> &clipObject);
protected:
    void initialize();
    void dispose();
};

#endif

