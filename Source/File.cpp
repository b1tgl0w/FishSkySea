//File: File.cpp
//Author:   John Miner
//Created:  06/19/12
//Purpose:  Singleton utility for file io (everything static singleton)
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License.
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
#include "../Header/File.hpp"

bool File::sectionToLines(std::string &line,
    std::istream &file, const std::string &sectionHeader,
    const std::string &sectionFooter)
{
    std::vector<std::string> lines;
    bool found = sectionToLines(lines, file, sectionHeader, sectionFooter);

    if( !found )
        return found;

    line = lines[0];

    return found;
}

bool File::sectionToLines(std::vector<std::string> &lines,
    std::istream &file, const std::string &sectionHeader,
    const std::string &sectionFooter)
{
    char line[1024];
    bool found = false;
    int currentPosition = file.tellg();

    while( !file.eof() )
    {
        file.getline(line, 1023);

        if( line == sectionHeader )
            break;
    }

    while( !file.eof() )
    {
        file.getline(line, 1023);

        if( line == sectionFooter )
        {
            found = true;
            break;
        }

        lines.push_back(line);
    }

    if( found == false )
        file.seekg(currentPosition);

    return found;
}

