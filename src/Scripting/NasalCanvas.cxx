// NasalCanvas.cxx -- expose Canvas classes to Nasal
//
// Written by James Turner, started 2012.
//
// Copyright (C) 2012 James Turner
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

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "NasalCanvas.hxx"
#include <Canvas/canvas_mgr.hxx>
#include <Main/globals.hxx>

#include <osgGA/GUIEventAdapter>

#include <simgear/sg_inlines.h>

#include <simgear/canvas/Canvas.hxx>
#include <simgear/canvas/elements/CanvasElement.hxx>

#include <simgear/nasal/cppbind/from_nasal.hxx>
#include <simgear/nasal/cppbind/to_nasal.hxx>
#include <simgear/nasal/cppbind/NasalHash.hxx>
#include <simgear/nasal/cppbind/Ghost.hxx>

extern naRef propNodeGhostCreate(naContext c, SGPropertyNode* n);

namespace sc = simgear::canvas;

template<class Element>
naRef elementGetNode(naContext c, Element& element)
{
  return propNodeGhostCreate(c, element.getProps());
}

typedef nasal::Ghost<sc::CanvasPtr> NasalCanvas;
typedef nasal::Ghost<sc::ElementPtr> NasalElement;
typedef nasal::Ghost<sc::GroupPtr> NasalGroup;

#if 0
typedef osg::ref_ptr<osgGA::GUIEventAdapter> GUIEventPtr;

class NasalCanvasEvent:
  public NasalObject<GUIEventPtr, NasalCanvasEvent>
{
  public:

    naRef getEventType(naContext c, const GUIEventPtr& event)
    {
#define RET_EVENT_STR(type, str)\
  case osgGA::GUIEventAdapter::type:\
    return nasal::to_nasal(c, str);

      switch( event->getEventType() )
      {
        RET_EVENT_STR(PUSH,         "push");
        RET_EVENT_STR(RELEASE,      "release");
        RET_EVENT_STR(DOUBLECLICK,  "double-click");
        RET_EVENT_STR(DRAG,         "drag");
        RET_EVENT_STR(MOVE,         "move");
        RET_EVENT_STR(SCROLL,       "scroll");
        RET_EVENT_STR(KEYUP,        "key-up");
        RET_EVENT_STR(KEYDOWN,      "key-down");

#undef RET_EVENT_STR

        default:
          return naNil();
      }
    }
};
#endif

static naRef f_createCanvas(naContext c, naRef me, int argc, naRef* args)
{
  CanvasMgr* canvas_mgr =
    static_cast<CanvasMgr*>(globals->get_subsystem("Canvas"));
  if( !canvas_mgr )
    return naNil();

  return NasalCanvas::create(c, canvas_mgr->createCanvas());
}

naRef f_canvasCreateGroup( sc::Canvas& canvas,
                           naContext c,
                           int argc,
                           naRef* args )
{
  std::string name;
  if( argc > 0 )
    name = nasal::from_nasal<std::string>(c, args[0]);

  return NasalGroup::create(c, canvas.createGroup(name));
}

naRef initNasalCanvas(naRef globals, naContext c, naRef gcSave)
{
  NasalCanvas::init("Canvas")
    .member("_node_ghost", &elementGetNode<sc::Canvas>)
    .member("size_x", &sc::Canvas::getSizeX)
    .member("size_y", &sc::Canvas::getSizeY)
    .method_func<&f_canvasCreateGroup>("createGroup");
  NasalElement::init("canvas.Element")
    .member("_node_ghost", &elementGetNode<sc::Element>);
  NasalGroup::init("canvas.Group")
    .bases<NasalElement>();

  nasal::Hash globals_module(globals, c),
              canvas_module = globals_module.createHash("canvas");

  canvas_module.set("_newCanvasGhost", f_createCanvas);

  return naNil();
}