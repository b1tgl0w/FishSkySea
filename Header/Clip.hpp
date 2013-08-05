//File: Clip.hpp
//Author:   John Miner
//Created:  03/01/12
//Modified: 03/01/12
//Purpose:  Keep track of what needs to be clipped and by how much
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

#ifndef CLIP_HPP_
#define CLIP_HPP_

#include <vector>
#ifdef linux
#include <SDL/SDL.h> 
#else
#include <SDL.h>
#endif
#include "boost/shared_ptr.hpp"
#include "Layout.hpp"
#include "Dimension.hpp"
#include "Point.hpp"
#include "FrameCleanupSubscriber.hpp"

class Clip 
{
public:
    Clip();
    Clip(const Clip &rhs);
    Clip &operator=(const Clip &rhs);
    ~Clip();
    SDL_Rect generateClipRectangle(const Point &clipPosition,
        const Dimension &clipSize);
    void onlyBoundary(const Point &position, const Dimension &size);
    void merge(const Clip &mergeWith);
protected:
    void initialize();
    void dispose();
private:
   Point position;
   Dimension size;
   bool hasBoundary;
};

#endif

