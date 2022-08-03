#include "header.h"
#include "proto.h"

void costVolume(
 int width,
 int height,
 int *img1_arr,
 int *img2_arr,
 int min_d,
 int max_d,
 int radius,
 double gamma_p,
 double gamma_c,
 double max_cost_col,
 double max_cost_grad,
 double alpha,
 double **cost_volume_arr
)

{

 double *img1_grayscale_arr;
 double *img2_grayscale_arr;
 double *img1_gradient_x_arr;
 double *img2_gradient_x_arr;
 int d;

 /*
 Allocate memory for the grayscale version of img1_arr
 */

 img1_grayscale_arr= (double *)calloc(width*height,sizeof(double));

 /*
 Get the grayscale version of img1_arr
 */

 rgb_to_grayscale(
  width,
  height,
  img1_arr,
  img1_grayscale_arr
 );

 /*
 Allocate memory for the grayscale version of img2_arr
 */

 img2_grayscale_arr= (double *)calloc(width*height,sizeof(double));

 /*
 Get the grayscale version of img2_arr
 */
 
 rgb_to_grayscale(
  width,
  height,
  img2_arr,
  img2_grayscale_arr
 );

 /*
 Get the gradient in x direction for img1_grayscale_arr
 */

 img1_gradient_x_arr= (double *)calloc(width*height,sizeof(double));

 gradient_x(
  width,
  height,
  img1_grayscale_arr,
  img1_gradient_x_arr
 );

 /*
 Get the gradient in x direction for img2_grayscale_arr
 */

 img2_gradient_x_arr= (double *)calloc(width*height,sizeof(double));

 gradient_x(
  width,
  height,
  img2_grayscale_arr,
  img2_gradient_x_arr
 );

 /*
 Compute raw matching cost for all disparities
 */

 for ( d= min_d ; d<= max_d ; d++ ) {

    /* 
    Compute the cost for that layer of the cost volume
    */

    costLayer(
     width,
     height,
     img1_arr,
     img2_arr,
     img1_gradient_x_arr,
     img2_gradient_x_arr,
     max_cost_col,
     max_cost_grad,
     alpha,
     d,
     cost_volume_arr[d-min_d]
    );
 }

 /*
 Free img1_grayscale_arr 
 */

 free(img1_grayscale_arr);

 /*
 Free img2_grayscale_arr
 */

 free(img2_grayscale_arr);

 /*
 Free img1_gradient_x_arr
 */

 free(img1_gradient_x_arr);

 /*
 Free img2_gradient_x_arr
 */

 free(img2_gradient_x_arr);

}
