ifndef LLVM_HOME
  $(error You must define LLVM_HOME so that the OpenMP library version providing the OMPT API can be found)
endif

# ----------------------------------
# set up OpenMP runtime
# ----------------------------------

LIB_DIR = $(LLVM_HOME)/lib$(LLVM_OMP_LIBDIR_SUFFIX)
LIB = $(LIB_DIR)/libomp.so

LIBS = -Wl,-rpath=$(LIB_DIR) $(LIB) -lm

# ----------------------------------
# include path for ompt.h and omp.h
# ----------------------------------
INCLUDES = -I$(LLVM_HOME)/include  -I.


CC = clang -fPIC -fPIE -gdwarf-3 -std=c11 -O3

#CC = clang -fPIC -fPIE -gdwarf-3 -std=c11 -fsanitize=address -fno-omit-frame-pointer -O3
#CC = clang -gdwarf-3 -std=c11 -O3
CXX = clang++ -fPIC -fPIE -gdwarf-3 -std=c++11 -O3

#CXX = clang++ -fPIC -fPIE -gdwarf-3 -std=c++11 -fsanitize=address -fno-omit-frame-pointer -O3
#CXX = clang++ -gdwarf-3 -std=c++11 -O3

OMPFLAGS = -fopenmp
BASE_FLAGS= -g $(INCLUDES)
FLAGS = $(OMPFLAGS) $(BASE_FLAGS) -mcx16 

all: libomprace

libomprace: ompt_handlers.o util.o TaskDependency.o LockSet.o openmp_dpst.o 
	ar r libomprace.a ompt_handlers.o openmp_dpst.o util.o TaskDependency.o LockSet.o


%.o : %.c 
	$(CC)  -c $(FLAGS) -o $@ $<

%.o : %.cpp 
	$(CXX) -c $(FLAGS) $(CPPFLAGS) -o $@ $<


clean:
	rm -rf *.o *.a *~

