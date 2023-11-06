CC=g++
SRC=$(PWD)/src
BUILDDIR=$(PWD)/builds
MKDIR_P = mkdir -p

all: build_dir compress uncompress

build_dir: $(BUILDDIR)

$(BUILDDIR):
	${MKDIR_P} $(BUILDDIR)

uncompress: $(SRC)
	ln -s $(BUILDDIR)/compress $(BUILDDIR)/uncompress

compress: $(SRC)
	g++ -o $(BUILDDIR)/compress $(SRC)/huffman.cc

clean:
	rm -rf *~ $(BUILDDIR)