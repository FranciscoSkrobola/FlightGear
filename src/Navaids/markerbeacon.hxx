// markerbeacon.hxx -- marker beacon class
//
// Written by James Turner, started December 2008.
//
// Copyright (C) 2008  Curtis L. Olson - http://www.flightgear.org/~curt
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
// $Id$


#ifndef _FG_MARKERBEACON_HXX
#define _FG_MARKERBEACON_HXX

#include <simgear/compiler.h>

#include "positioned.hxx"


class FGMarkerBeaconRecord : public FGPositioned
{
public:

  FGMarkerBeaconRecord(PositionedID aGuid, Type aTy, PositionedID aRunway, const SGGeod& aPos);
private:
  
  PositionedID _runway;
};

#endif // _FG_MARKERBEACON_HXX
