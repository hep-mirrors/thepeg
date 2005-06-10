CLEANFILES = AllInterfaces.h

html-clean:
	rm -rf refman-html

html-local: refman-html

refman-html: refman.conf refman.h
	./fixinterfaces.pl AllInterfaces.h
	doxygen $<
