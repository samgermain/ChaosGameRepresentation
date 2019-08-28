CXXFLAGS = -Wall -Wextra
# -I /opt/local/include/

LDFLAGS = -lnetpbm 
# -L /opt/local/lib

CGR_OBJ = cgr.o cgr_aux.o cgr_plot.o

TESTCGR_PLOT_OBJ = cgr_aux.o cgr_plot.o test_cgr_plot.o

TESTCGR_AUX_OBJ = cgr_aux.o test_cgr_aux.o cgr_plot.o

.PHONY: all tests clean

all: cgr tests

cgr: $(CGR_OBJ)
	g++ $(CGR_OBJ) $(LDFLAGS) -o cgr

tests: test_cgr_aux test_cgr_plot

test_cgr_aux: $(TESTCGR_AUX_OBJ)
	g++ $(CXXFLAGS) $(LDFLAGS) -g $(TESTCGR_AUX_OBJ) -o test_cgr_aux

test_cgr_plot: $(TESTCGR_PLOT_OBJ)
	g++ $(CXXFLAGS) $(LDFLAGS) -g $(TESTCGR_PLOT_OBJ) -o test_cgr_plot

cgr_plot.o: cgr_plot.cc cgr_aux.h cgr.h cgr_plot.h
	g++ $(CXXFLAGS) -c cgr_plot.cc

cgr_aux.o: cgr_aux.cc cgr_aux.h cgr.h cgr_plot.h
	g++ $(CXXFLAGS) -c cgr_aux.cc

cgr.o: cgr.cc cgr_aux.h cgr.h cgr_plot.h
	g++ $(CXXFLAGS) -c cgr.cc

test_cgr_aux.o: test_cgr_aux.cc cgr_aux.h cgr.h cgr_plot.h
	g++ $(CXXFLAGS) -c test_cgr_aux.cc

test_cgr_plot.o: test_cgr_plot.cc cgr_aux.h cgr.h cgr_plot.h
	g++ $(CXXFLAGS) -c test_cgr_plot.cc

clean:
	rm -f cgr_plot.o cgr_aux.o cgr_aux.o cgr.o test_aux.o test_plot.o test_cgr_plot.o
	rm -f cgr tests test_cgr_aux test_cgr_plot