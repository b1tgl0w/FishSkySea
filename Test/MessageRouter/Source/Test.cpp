//File: Test.cpp
//Author:   John Miner
//Created:  09/13/13
//Purpose:  Verify that MessageRouter works.
//Copyright 2013 John Miner
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

#include <iostream>
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/shared_ptr.hpp"
#include "../../../Header/MessageRouter.hpp"
#include "../../../Header/MessageReceiver.hpp"
#include "../../../Header/MessageData.hpp"
#include "../../../Header/Point.hpp"

class Point;

class TestReceiver : public MessageReceiver
{
public:
    void sendMessage(const boost::uuids::uuid &senderId, const MessageEnum
        &message, const TypeHint &typeHint, boost::shared_ptr<MessageData>
        data); 
};

void TestReceiver::sendMessage(const boost::uuids::uuid &senderId, const MessageEnum
    &message, const TypeHint &typeHint, boost::shared_ptr<MessageData>
    data) 
{
    if( typeHint == TypeHint::Point ) 
    {
        boost::shared_ptr<Point> pt = boost::dynamic_pointer_cast<Point>(data);

        if( !pt )
        {
            std::cout << "error" << std::endl;
            return;
        }

        std::cout << pt->x << "\t" << pt->y << std::endl;
        
    }
}

int main(int argc, char **argv)
{
    boost::shared_ptr<TestReceiver> tr(new TestReceiver);
    boost::shared_ptr<MessageReceiver> mr(tr);
    MessageRouter router;
    router.subscribeToMessage(MessageEnum::FISH_MOVE, mr);
    boost::shared_ptr<Point> pt(new Point(1.0, 3.0));
    boost::shared_ptr<MessageData> md(pt);
    boost::uuids::uuid id = boost::uuids::random_generator()();
    router.sendMessage(id, MessageEnum::FISH_MOVE, TypeHint::Point, md);
}

