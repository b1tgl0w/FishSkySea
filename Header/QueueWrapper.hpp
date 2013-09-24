//File: QueueWrapper.hpp
//Author:   John Miner
//Created:  09/20/13
//Purpose:  Queue wrapper
//          
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

#ifndef QUEUE_WRAPPER_HPP_
#define QUEUE_WRAPPER_HPP_

#include <queue>
#include "MessageData.hpp"

/****IMPORTANT NOTE*****/
//BEWARE OF CYCLE SHARED_PTRS
template<typename T>
class QueueWrapper : public MessageData
{
public:
    QueueWrapper();
    QueueWrapper(const QueueWrapper<T> &rhs);
    QueueWrapper<T> &operator=(const QueueWrapper<T> &rhs);
    ~QueueWrapper();
    std::queue<T> actualQueue;
};

template <typename T>
QueueWrapper<T>::QueueWrapper() : actualQueue() { }

template <typename T>
QueueWrapper<T>::QueueWrapper(const QueueWrapper<T> &rhs) : 
    actualQueue(rhs.actualQueue) { }

template <typename T>
QueueWrapper<T> &QueueWrapper<T>::operator=(const QueueWrapper<T> &rhs)
{
    if( &rhs == this )
        return *this;

    actualQueue = rhs.actualQueue;

    return *this;
}

template <typename T>
QueueWrapper<T>::~QueueWrapper() { }

#endif

