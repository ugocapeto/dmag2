#include "header.h"
#include "proto.h"

void support(
 int width,
 int height,
 int *img_arr,
 int i_inp,
 int j_inp,
 int radius,
 double *dist_c,
 double *weight_arr
)

/*
Compute the support weights for the window centered at pixel (i_inp,j_inp)
w/r to color 
*/

{

 int dist;
 int i_offset;
 int j_offset;
 int ind;
 int i;
 int j;
 int ind_inp;
 int cind;

 /*
 Initialize the weights
 */

 for ( i_offset= -radius ; i_offset<= +radius ; i_offset++ ) {
    for ( j_offset= -radius ; j_offset<= +radius ; j_offset++ ) {
       ind= (i_offset+radius)*(2*radius+1)+j_offset+radius;
       weight_arr[ind]= 0;
    }
 }

 if ( !(0<=j_inp && j_inp<width) ) {
    return;
 }

 /*
 Compute the weights
 */

 for ( i_offset= -radius ; i_offset<= +radius ; i_offset++ ) {
    i= i_inp+i_offset;
    if ( 0<=i && i<height ) {
       for ( j_offset= -radius ; j_offset<= +radius ; j_offset++ ) {
          j= j_inp+j_offset;
          if ( 0<=j && j<width ) {
             ind_inp= i_inp*width+j_inp;
             ind= i*width+j;
             dist= 0;
             for ( cind= 0 ; cind< 3 ; cind++ ) {
                dist+= abs(img_arr[3*ind+cind]-img_arr[3*ind_inp+cind]);
             }
             ind= (i_offset+radius)*(2*radius+1)+j_offset+radius;
             weight_arr[ind]= dist_c[dist];
          }
       } 
    }
 }

}
