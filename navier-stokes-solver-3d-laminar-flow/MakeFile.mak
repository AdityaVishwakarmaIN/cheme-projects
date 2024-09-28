CXX = g++
CXXFLAGS = -O2 -std=c++11

SOURCES = main.cpp Grid3D.cpp VectorField3D.cpp ScalarField3D.cpp BoundaryConditions.cpp Solver.cpp SparseMatrix.cpp Utilities.cpp
HEADERS = Grid3D.h VectorField3D.h ScalarField3D.h BoundaryConditions.h Solver.h SparseMatrix.h Utilities.h Constants.h

TARGET = NavierStokesSolver

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) *.o *.vtk