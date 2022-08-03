#include "header.h"
#include "proto.h"

void costLayer(
 int width,
 int height,
 int *img1_arr,
 int *img2_arr,
 double *img1_gradient_x_arr,
 double *img2_gradient_x_arr,
 double max_cost_col,
 double max_cost_grad,
 double alpha,
 int d,
 double *cost_arr
)

{

 double cost_col;
 double cost_grad;
 int i;
 int j;
 int ind1;
 int ind2;
 double cost;
 int cind;

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind1= i*width+j;
       ind2= i*width+j-d;

       /*
       Initialize the raw cost
       */

       cost_col= max_cost_col;
       cost_grad= max_cost_grad;
       cost= (1-alpha)*cost_col+alpha*cost_grad;
       cost_arr[ind1]= cost;

       if ( j-d < 0 )
        continue;
       if ( j-d > width-1 )
        continue;

       /*
       Let's consider the raw color matching cost
       */

       cost_col= 0;
       for ( cind= 0 ; cind< 3 ; cind++ ) {
          cost_col+= fabs(img1_arr[3*ind1+cind]-img2_arr[3*ind2+cind]);
       }
       cost_col/= 3;

       if ( cost_col > max_cost_col )
        cost_col= max_cost_col;

       /*
       Let's consider the raw gradient matching cost
       */

       cost_grad= fabs(img1_gradient_x_arr[ind1]-img2_gradient_x_arr[ind2]);

       if ( cost_grad > max_cost_grad )
        cost_grad= max_cost_grad;

       /*
       Let's combine the color term and gradient term
       */

       cost= (1-alpha)*cost_col+alpha*cost_grad;

       /*
       Store into cost_arr
       */

       cost_arr[ind1]= cost;
    }
 }

}
