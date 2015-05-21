//File: Ocean.h
//Author:   John Miner
//Created:  10/04/11
//Modified: 10/04/11
//Purpose:  Container and "manager" of most game objects.
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

#ifndef OCEAN_HPP_
#define OCEAN_HPP_

#include <set>
#include <vector>
#include <map>
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "BoundingBox.hpp"
#include "Dimension.hpp"
#include "Collidable.hpp"
#include "Graphic.hpp"
#include "Depth.hpp"
#include "Clouds.hpp"
#include "CreditFish.hpp"

class OceanMode;
class Fish;
class SeaSnail;
class Seahorse;
class Shark;
class Line;
class Point;
class Direction;
class Renderer;
class MessageRouter;

class Ocean : public Collidable, public Graphic,
    public boost::enable_shared_from_this<Ocean>
{
friend class OceanState;
friend class GameState;
friend class CreditState;
public:
    explicit Ocean(const Dimension &screenSize, boost::shared_ptr<Renderer> &renderer,
        boost::shared_ptr<MessageRouter> &messageRouter);
    Ocean(const Ocean &rhs);
    Ocean &operator=(const Ocean &rhs);
    virtual ~Ocean();
    //_Must_ be called _immediately_ after ctor
    void initializeStates(); 
    //_Must_ be called _immediately_ after initializeStates
    void initializeSharedFromThis();
    void changeState(const OceanMode &oceanMode);
    bool isAboveSurface(const BoundingBox &fishBox, const Fish &fish);
    Direction hitEdge(const BoundingBox &fishBox);
    void addFish(boost::shared_ptr<Fish> &fish, const Depth &depth);
    void addCreditFish(boost::shared_ptr<CreditFish> &CreditFish);
    void addSeahorse(boost::shared_ptr<Seahorse> &seahorse, const Depth &depth);
    void alignWithBoundary(double &coordinate, const Direction &whichBoundary,
        const double offset = 1.0);
    void alignWithSurface(double &coordinate, const double offset = 1.0);
    void alignWithPerspectiveSurface(double &coordinate, const double offset = 1.0);
    void addCollidable(boost::weak_ptr<Collidable> collidable);
    void removeCollidable(boost::weak_ptr<Collidable> collidable);
    void checkCollisions(boost::shared_ptr<Collidable> &object,
        const BoundingBox &objectBox);
    void gameLive(bool live);
//Graphic
    void draw(boost::shared_ptr<Layout> &, Renderer &renderer);
    void loadImage(Renderer &renderer);
//Collidable
    void collidesWith(boost::shared_ptr<Collidable> &otherObject,
        const BoundingBox &otherBox);
    void collidesWithHook(boost::shared_ptr<Line> &hook,
        const BoundingBox &yourBox);
    void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox, const Direction &direction);
    void collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
    void collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
    void collidesWithShark(boost::shared_ptr<Shark> &shark,
        const BoundingBox &yourBox);
    void collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
        const BoundingBox &yourBox);
    void collidesWithFish(boost::shared_ptr<Fish> &fish,
        const BoundingBox &yourBox);
    void collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
        const BoundingBox &yourBox);
    void collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
        const BoundingBox &yourBox);
    void collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
        const BoundingBox &yourBox, const Direction &direction);
    void collidesWithCreditFish(boost::shared_ptr<CreditFish> &creditFish,
        const BoundingBox &yourBox);
    void collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
        const BoundingBox &yourBox, const Direction &seahorseFacing);
    void collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
        const BoundingBox &yourBox, const Direction &seahorseFacing);
    void collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
        const BoundingBox &yourBox);
    void collidesSharkBack(boost::shared_ptr<Shark> &shark,
        const BoundingBox & yourBox);
    void collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
    std::vector<boost::shared_ptr<Layout> > layoutsToAttach();
    boost::shared_ptr<boost::signals2::connection> subscribeToCreditFish(const std::string &name, 
        const CreditFish::OnCatchSlotType &slot);
protected:
    void initialize(const Dimension &screenSize);
    void dispose();
private:
    class OceanState
    {
    friend class Ocean;
    public:
        virtual void draw(boost::shared_ptr<Layout> &layout, 
            Renderer &renderer) = 0;
        virtual void checkCollisions(
            boost::shared_ptr<Collidable> &object, const BoundingBox &objectBox)
            = 0;
        virtual void gameLive(bool live) = 0;
        virtual void addCollidable(boost::weak_ptr<Collidable> collidable) = 0;
        virtual void removeCollidable(boost::weak_ptr<Collidable> collidable)
            = 0;
    };
    class GameState : public OceanState
    {
    friend class Ocean;
    public:
        GameState(boost::shared_ptr<Ocean> &oceanOwner);
        GameState(const GameState &rhs);
        GameState &operator=(const GameState &rhs);
        void draw(boost::shared_ptr<Layout> &layout, 
            Renderer &renderer);
        void checkCollisions(
            boost::shared_ptr<Collidable> &object, const BoundingBox &objectBox);
        void gameLive(bool live);
        void addCollidable(boost::weak_ptr<Collidable> collidable);
        void removeCollidable(boost::weak_ptr<Collidable> collidable);
    private:
        boost::weak_ptr<Ocean> oceanOwner;
    };
    class CreditState : public OceanState
    {
    friend class Ocean;
    public:
        CreditState(boost::shared_ptr<Ocean> &oceanOwner);
        CreditState(const CreditState &rhs);
        CreditState &operator=(const CreditState &rhs);
        void draw(boost::shared_ptr<Layout> &layout, 
            Renderer &renderer);
        void checkCollisions(
            boost::shared_ptr<Collidable> &object, const BoundingBox &objectBox);
        void gameLive(bool live);
        void addCollidable(boost::weak_ptr<Collidable> collidable);
        void removeCollidable(boost::weak_ptr<Collidable> collidable);
    private:
        boost::weak_ptr<Ocean> oceanOwner;
    };

    static double &OCEAN_EDGE_X();
    static double &OCEAN_EDGE_Y();
    const static double &OCEAN_SURFACE_WIDTH();
    const static double &OCEAN_SURFACE_HEIGHT();
    const static double &OCEAN_FLOOR_Y();
    const static double &OCEAN_FLOOR_WIDTH();
    const static double &OCEAN_FLOOR_HEIGHT();
    const static Point &SEA_SNAIL_POSITION();
    const static Point &SEA_HORSE_POSITION();
    const static Point &SHARK_POSITION();
    void addFish(const Depth &depth); //Overloaded from public
    double getDepthY(const Depth &depth);
    double getRandomDepthY();
    double getFishStartingX();
    std::set<boost::weak_ptr<Collidable> > collidables;
    std::set<boost::weak_ptr<Collidable> > creditCollidables;
    std::vector<boost::shared_ptr<Fish> > fishes;
    std::vector<boost::shared_ptr<CreditFish> > creditFishes;
    boost::shared_ptr<SeaSnail> seaSnail;
    boost::shared_ptr<Seahorse> seahorse;
    boost::shared_ptr<Shark> shark;
    std::map<Depth, double> depthCoordinates;
    boost::shared_ptr<OceanState> state;
    boost::shared_ptr<GameState> gameState;
    boost::shared_ptr<CreditState> creditState;
    Dimension screenSize;
    boost::shared_ptr<Point> oceanEdgePosition;
    boost::shared_ptr<Dimension> oceanEdgeSize;
    boost::shared_ptr<Point> oceanSurfacePosition;
    boost::shared_ptr<Dimension> oceanSurfaceSize;
    boost::shared_ptr<Point> oceanFloorPosition;
    boost::shared_ptr<Dimension> oceanFloorSize;
    BoundingBox oceanBox;
    BoundingBox oceanSurfaceBox;
    BoundingBox oceanFloorBox;
    boost::shared_ptr<Clouds> clouds;
    boost::shared_ptr<Renderer> renderer;
    boost::shared_ptr<MessageRouter> messageRouter;
    Dimension screenDimension;
};

#endif

