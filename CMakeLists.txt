cmake_minimum_required(VERSION 3.12)
project(Pythia8Example)

set(CMAKE_CXX_STANDARD 11)

add_executable(Pythia8Example main.cpp)
target_link_libraries(Pythia8Example pythia8 boost_iostreams z dl LHAPDF HepMC)
target_link_libraries(Pythia8Example Gui Core Imt RIO Net Hist Graf Graf3d Gpad Tree TreePlayer Rint Postscript Matrix Physics MathCore Thread MultiProc m dl)