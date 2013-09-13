//File: MessageRouter.hpp
//Author:   John Miner
//Created:  09/12/13
//Purpose: Route messages to objects that want them
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

#ifndef MESSAGE_ROUTER_
#define MESSAGE_ROUTER_

#include <map>
#include "boost/shared_ptr.hpp"
#include "boost/uuid/uuid.hpp"

class MessageReceiver;
class MessageData;

enum MessageEnum { FishMove };
enum TypeHint { Point, Dimension };

class MessageRouter
{
public:
    MessageRouter();
    MessageRouter(const MessageRouter &rhs);
    MessageRouter &operator=(const MessageRouter &rhs);
    void sendMessage(const boost::uuids::uuid &senderId, const MessageEnum &message, 
        const TypeHint &typeHint, boost::shared_ptr<MessageData> &data);
    void subscribeToMessage(const MessageEnum &message, boost::shared_ptr<
        MessageReceiver> mr);
    void unsubscribeToMessage(const MessageEnum &message, boost::shared_ptr<
        MessageReceiver> mr);
private:
    std::multimap<MessageEnum, boost::shared_ptr<MessageReceiver> >
        subscribers;
};

#endif

