#include "header.h"

void* calculate_pi( void* arg )
{
  unsigned seed = time( NULL );

  int circle_points = 0;
  int square_points = 0;
  int intervals = *( (int*)arg );

  for ( int i = 0; i < intervals * intervals; ++i ) {
    double rand_x = (double)rand_r( &seed ) / RAND_MAX;
    double rand_y = (double)rand_r( &seed ) / RAND_MAX;

    if ( rand_x * rand_x + rand_y * rand_y <= 1 ) {
      ++circle_points;
    }

    ++square_points;
  }

  double pi = ( 4.0 * circle_points ) / square_points;

  printf( "PI = %lf, times = %d\n", pi, intervals * intervals );

  pthread_exit( 0 );
}

int main()
{
  clock_t start, delta;

  start = clock();

  pthread_t threads[10];

  int args[10];

  for ( int i = 0; i < 10; ++i ) {
    args[i] = 1000 * ( i + 1 );
    pthread_create( threads + i, NULL, calculate_pi, args + i );
  }

  for ( int i = 0; i < 10; ++i ) {
    pthread_join( threads[i], NULL );
  }

  delta = clock() - start;
  printf( "totle time = %lfs\n", (double)delta / CLOCKS_PER_SEC );

  return 0;
}
