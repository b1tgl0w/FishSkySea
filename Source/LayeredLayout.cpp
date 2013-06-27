//File: LayeredLayout.cpp
//Author:   John Miner
//Created:  02/27/12
//Modified: 02/27/12
//Purpose:  Section sublayouts and images into layers
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/LayeredLayout.hpp"
#include "../Header/EmptyLayout.hpp"

LayeredLayout::LayeredLayout(const int
    numberOfLayers, boost::shared_ptr<FitStrategy> &fitStrategy)
{
    boost::shared_ptr<Clip> clipObject(new Clip);
    Point tmpPosition = { 0.0, 0.0 };
    position = tmpPosition;
    Dimension tmpSize = { 0.0, 0.0 };
    size = tmpSize;
    initialize(numberOfLayers, fitStrategy, clipObject);
}

LayeredLayout::LayeredLayout(const LayeredLayout &rhs) : position(rhs.position),
size(rhs.size)
{
    dispose();
    initialize(rhs.layers.size(), rhs.fitStrategy,
        rhs.clipObject);
}

LayeredLayout &LayeredLayout::operator=(const LayeredLayout &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    position = rhs.position;
    size = rhs.size;
    initialize(rhs.layers.size(), rhs.fitStrategy,
        rhs.clipObject);

    return *this;
}

LayeredLayout::~LayeredLayout()
{
    dispose();
}

void LayeredLayout::initialize(const int 
    numberOfLayers, const boost::shared_ptr<FitStrategy> &fitStrategy,
    const boost::shared_ptr<Clip> &clipObject)
{
    //Position and size cannot be set until their owner provides that data
    //Initialize to 0 until then
    position.x = 0.0;
    position.y = 0.0;
    size.width = 0.0;
    size.height = 0.0;
    //this->numberOfLayers = numberOfLayers;
    this->fitStrategy = fitStrategy;
    this->clipObject = clipObject;
}

void LayeredLayout::dispose()
{
}

void LayeredLayout::drawWhenReady(RendererElement &re)
{
    //Throw exception, not allowed to directly add REs to LayeredLayout
}

void LayeredLayout::drawWhenReady(boost::shared_ptr<RendererElement>
    &rendererElement, boost::shared_ptr<Layout> &callerLayout)
{
    std::vector<boost::shared_ptr<Layout> >::iterator it = layers.begin();
    for(int i = 0; it != layers.end(); 
        ++it, ++i)
    {
        if( this->toDraw.size() - 1 < i || this->toDraw.empty() )
            toDraw.push_back(emptyList);
        if( *it == callerLayout )
            toDraw[i].push_back(rendererElement);
    }
}

void LayeredLayout::drawWhenReady(const std::list<boost::shared_ptr<RendererElement> >
    &toDraw, boost::shared_ptr<Layout> &callerLayout)
{
    std::vector<boost::shared_ptr<Layout> >::iterator it = layers.begin();
    for(int i = 0; it != layers.end(); 
        ++it, ++i)
    {
        if( this->toDraw.size() - 1 < i || this->toDraw.empty() )
            this->toDraw.push_back(emptyList);
        if( *it == callerLayout )
            this->toDraw[i].insert(this->toDraw[i].begin(), toDraw.begin(),
                toDraw.end());
    }
}

void LayeredLayout::render()
{
    for( std::vector<boost::shared_ptr<Layout> >::iterator it = layers.begin();
        it != layers.end(); ++it )
        (*it)->render();

    if( toDraw.empty() )
        return;

    boost::shared_ptr<Layout> sharedOwner = owner.lock();
    if( !sharedOwner )
    {
        toDraw.clear();
        return;
    }

    int greatestZ = -1;
    boost::shared_ptr<Layout> layout(shared_from_this());
    clipObject->onlyBoundary(position, size);

    for( std::vector<std::list<boost::shared_ptr<RendererElement> > >::iterator
        it = toDraw.begin(); it != toDraw.end(); ++it )
    {
        if( it > toDraw.begin() && !(*(it - 1)).empty() )
            greatestZ = (*((it-1)->begin()))->greatestZ(*(it - 1));

        for( std::list<boost::shared_ptr<RendererElement> >::iterator 
            it2 = it->begin(); it2 != it->end(); ++it2 )
            (*it2)->layerBy(greatestZ + 1);

        fitStrategy->fit(*it, position, size, clipObject);
        sharedOwner->drawWhenReady(*it, layout);
    }

    toDraw.clear();
}

void LayeredLayout::scale(const Dimension &size)
{
    this->size = size;

    for( std::vector<boost::shared_ptr<Layout> >::iterator it = layers.begin();
        it != layers.end(); ++it )
        (*it)->scale(size);
}

void LayeredLayout::scale(const DimensionPercent &dimensionPercent)
{
   size.width *= dimensionPercent.widthPercent;
   size.height *= dimensionPercent.heightPercent;

   for( std::vector<boost::shared_ptr<Layout> >::iterator it = layers.begin();
        it != layers.end(); ++it )
        (*it)->scale(dimensionPercent);
}

void LayeredLayout::moveTo(const Point &newPosition)
{
    Point offset = { newPosition.x - position.x, newPosition.y - position.y };
    moveBy(offset);
}

void LayeredLayout::moveBy(const Point &offset)
{
    position.x += offset.x;
    position.y += offset.y;

    for( std::vector<boost::shared_ptr<Layout> >::iterator it = layers.begin();
        it != layers.end(); ++it )
    {
        (*it)->moveBy(offset);
    }
}

bool LayeredLayout::isHere(const Point &position)
{
    return this->position.x == position.x && this->position.y == position.y;
}

boost::shared_ptr<Layout> LayeredLayout::operator[](int layer)
{
    return layers[layer];
}

void LayeredLayout::addLayout(boost::shared_ptr<Layout> &layout, int layer)
{
    const Point TOP_LEFT = { 0.0, 0.0 };

    if(layer - (int) layers.size() > 0 )
    {
        boost::shared_ptr<Layout> emptyLayout(new EmptyLayout);
        std::vector<boost::shared_ptr<Layout> >::iterator it = layers.end();
        layers.insert(it, layer - (int) layers.size(), emptyLayout);
        layers.push_back(layout);
    }
    else if( layer - (int) layers.size() == 0 )
        layers.push_back(layout);
    else
        layers[layer] = layout;

    layout->moveTo(TOP_LEFT);
    layout->scale(size);
    boost::shared_ptr<Layout> sharedThis(shared_from_this());
    layout->own(sharedThis);
}

void LayeredLayout::removeLayout(boost::shared_ptr<Layout> &layout, int layer)
{
    if(layer - (int) layers.size() > 0 )
    {
    }
    else if( layer - (int) layers.size() == 0 )
    {
    }
    else
    {
        if( layers[layer] == layout )
        {
            boost::shared_ptr<Layout> emptyLayout(new EmptyLayout);
            layers[layer] = emptyLayout;
        }
    }
}

void LayeredLayout::own(const boost::weak_ptr<Layout> &owner)
{
    this->owner = owner;
}

