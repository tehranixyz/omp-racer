#include "omprace.h"
#include <omp.h>
#include "util.h"
#include <stdio.h>

#define TEST_NUM_THREADS 2
/** task wait variations example 
 *  3 levels of nesting, 1 taskwait
 *  variation B
 */
int main(int argc, char* argv[])
{
  omprace_init();
  #pragma omp parallel num_threads(TEST_NUM_THREADS)
  {
    printf("parallel region, tid=%d\n", omp_get_thread_num());
    serialwork(10000000);//a
    #pragma omp single
    {
      serialwork(10000000);//b
      #pragma omp task
      {
        serialwork(10000000);//c
        #pragma omp task
        {   
          serialwork(10000000);//d
          #pragma omp task
          {   
            serialwork(10000000);//e 
          }
          serialwork(5000000);//f_pre 
          #pragma omp taskwait
          serialwork(5000000);//f_post
        }
        serialwork(10000000);//g
      }        
      serialwork(10000000);//h
    }
  }
  omprace_fini();
  return 0;
}