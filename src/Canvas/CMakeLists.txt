include(FlightGearComponent)

set(SOURCES
  canvas_mgr.cxx
  FGCanvasSystemAdapter.cxx
  gui_mgr.cxx
  window.cxx
)

set(HEADERS
  canvas_mgr.hxx
  FGCanvasSystemAdapter.hxx
  gui_mgr.hxx
  window.hxx
)

flightgear_component(Canvas "${SOURCES}" "${HEADERS}")