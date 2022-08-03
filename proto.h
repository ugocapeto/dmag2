int color_distance_squared(
 int width,
 int height,
 int *image_arr,
 int i1,
 int j1,
 int i2,
 int j2
);

void compute_disparity_map(
 int width,
 int height,
 int *image1_arr,
 int *image2_arr,
 int min_d,
 int max_d,
 int radius,
 double alpha,
 double gamma_p,
 double gamma_c,
 double max_cost_color,
 double max_cost_gradient,
 int disp_tol,
 int radius_smooth,
 double sigma_space,
 double sigma_color,
 int ds_factor,
 int **pdisp1_arr,
 int **pdisp2_arr,
 int **pocc1_arr,
 int **pocc2_arr
);

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
);

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
);

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
);

void detect_occlusion(
 int width,
 int height,
 int *disp1_arr,
 int *disp2_arr,
 int min_d,
 int max_d,
 int disp_tol,
 int *occ1_arr
);

void disparityAW(
 int width,
 int height,
 int *img1_arr,
 int *img2_arr,
 int *disp1_arr,
 int *disp2_arr,
 int min_d,
 int max_d,
 int radius,
 double gamma_p,
 double gamma_c,
 double max_cost_col,
 double max_cost_grad,
 double alpha
);

void downsample_image(
 double *inp_I,
 int inp_xdim,
 int inp_ydim,
 double *out_I,
 int out_xdim,
 int out_ydim,
 double factor
);

void downsample_image_dimensions(
 int inp_xdim,
 int inp_ydim,
 int *pout_xdim,
 int *pout_ydim,
 double factor
);

void downsample_image_int(
 int *inp_I_int,
 int inp_xdim,
 int inp_ydim,
 int *out_I_int,
 int out_xdim,
 int out_ydim,
 double factor
);

void downsample_rgb_image(
 double *inp_I_rgb,
 int inp_xdim,
 int inp_ydim,
 double *out_I_rgb,
 int out_xdim,
 int out_ydim,
 double factor
);

void downsample_rgb_image_int(
 int *inp_I_rgb_int,
 int inp_xdim,
 int inp_ydim,
 int *out_I_rgb_int,
 int out_xdim,
 int out_ydim,
 double factor
);

void fill_occlusion_left_right(
 int width,
 int height,
 int *disp_arr,
 int *occ_arr,
 int min_d,
 int max_d
);

void fill_occlusion_right_left(
 int width,
 int height,
 int *disp_arr,
 int *occ_arr,
 int min_d,
 int max_d
);

void gaussian_blur_image(
 double *I,
 int xdim,
 int ydim,
 double sigma,
 int precision
);

void gradient_x(
 int width,
 int height,
 double *image,
 double *gradient
);

void median(
 int width,
 int height,
 int *image_arr,
 int radius,
 int *median_arr
);

int median_histo(
 int min_d,
 int max_d,
 double *hist
);

void normalize_image(
 int *inp_I,
 int *out_I,
 int size,
 int min_val,
 int max_val
);

void rgb_to_grayscale(
 int width,
 int height,
 int *image_rgb,
 double *image_grayscale
);

void smooth_occlusion_weighted_median(
 int width,
 int height,
 int *image_arr,
 int *disp_arr,
 int *occ_arr,
 int min_d,
 int max_d,
 int radius,
 double sigma_space,
 double sigma_color
);

void support(
 int width,
 int height,
 int *img_arr,
 int i_inp,
 int j_inp,
 int radius,
 double *dist_c,
 double *weigth_arr
);

void weighted_histo(
 int width,
 int height,
 int *image_arr,
 int *disp_arr,
 int *occ_arr,
 int min_d,
 int max_d,
 int radius,
 double sigma_space,
 double sigma_color,
 int i_ref,
 int j_ref,
 double *hist_arr
);

void weighted_median(
 int width,
 int height,
 int *image_arr,
 int *disp_arr,
 int *occ_arr,
 int min_d,
 int max_d,
 int radius,
 double sigma_space,
 double sigma_color,
 int *new_disp_arr 
);
