#include "header.h"
#include "proto.h"

double costCombined(
 int width,
 int height,
 int radius,
 int i_inp,
 int j1_inp,
 int j2_inp,
 double *w1_arr,
 double *w2_arr,
 double *dist_p,
 double *cost_arr
)

{

 double num;
 double den;
 int i_offset;
 int i;
 int j_offset;
 int j1;
 int j2;
 int ind;
 double w1;
 double w2;
 double comb;
 int ind1;

 num= 0;
 den= 0;

 for ( i_offset= -radius ; i_offset<= +radius ; i_offset++ ) {
    i= i_inp+i_offset;
    if ( 0<=i && i<height ) {
       for ( j_offset= -radius ; j_offset<= +radius ; j_offset++ ) {
          j1= j1_inp+j_offset;
          j2= j2_inp+j_offset;
          if ( 0<=j1 && j1<width && 0<=j2 && j2<width ) {
             ind= (i_offset+radius)*(2*radius+1)+j_offset+radius;
             w1= w1_arr[ind];
             w2= w2_arr[ind];
             comb= dist_p[ind]*w1*w2;
             ind1= i*width+j1;
             num+= comb*cost_arr[ind1];
             den+= comb; 
          }
       }
    }
 }

 return (num/den);

}
