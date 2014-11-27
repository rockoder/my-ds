# TODO Add better dependency rules

GTEST_INSTALL_DIR=/home/rockoder/InstallConfig/gtest-1.7.0

CFLAGS = -std=c++11

INCLUDES = -I$(GTEST_INSTALL_DIR)/include -Iinclude

SDIR = include
LDIR = -L$(GTEST_INSTALL_DIR)/lib
LIBS = -lgtest -pthread

ODIR = bin
TDIR = test

all: TestBT TestBST

TestBT: $(SDIR)/BinaryTree.h
	g++ $(INCLUDES) $(TDIR)/TestMain.cpp $(LDIR) $(LIBS) $(CFLAGS) $(TDIR)/TestBT.cpp -o $(ODIR)/TestBT

TestBST: $(SDIR)/BinarySearchTree.h
	g++ $(INCLUDES) $(TDIR)/TestMain.cpp $(LDIR) $(LIBS) $(CFLAGS) $(TDIR)/TestBST.cpp -o $(ODIR)/TestBST

clean:
	rm -rf $(ODIR)/*	
