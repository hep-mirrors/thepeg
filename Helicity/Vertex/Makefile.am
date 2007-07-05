SUBDIRS = Scalar Vector Tensor

noinst_LTLIBRARIES = libThePEGVertex.la
libThePEGVertex_la_SOURCES = VertexBase.cc VertexBase.h \
	 VertexBase.fh VertexBase.icc
libThePEGVertex_la_LIBADD = Scalar/libThePEGSVertex.la \
	Vector/libThePEGVVertex.la \
	Tensor/libThePEGTVertex.la
