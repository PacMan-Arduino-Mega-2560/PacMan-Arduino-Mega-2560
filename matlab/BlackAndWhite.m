matrix3D = imread('stage.png');

matrix2D = rgb2gray(matrix3D);

BW = imbinarize(matrix2D);

imshow(BW);