% m-file for painting titles
% Creates a cell arrays with ground truth identification
% title = 33x1 cell-array of painting titles
% files = 33x3 cell-array of file names
% The rows of title correspond to the rows of files
% E.g. 01_1.jpg, 01_2.jpg 01_3.jpg are the_resurrection

title = { ...
	'the_resurrection';
	'edward_becher';
	'portrait_of_elizabeth';
	'adam_and_eve';
	'portrait_of_a_young_artist';
	'landscape';
	'vesuvius';
	'schloss_angenstien';
	'margaret_blagge';
	'sea_view';
	'village_festival';
	'gentleman';
	'musical_party';
	'sacrifice_of_jeroboam';
	'landscape_with_adam_and_eve';
	'the_painter';
	'the_conversation';
	'napoleon';
	'prison_of_saint-lazare';
	'her_majesty';
	'deposition';
	'daughters_of_jethro';
	'lament_of_saint_peter';
	'the_torment_of_tityus';
	'allegorical_landscape';
	'holy_trinity';
	'education_of_the_virgin';
	'saint_john';
	'madonna_and_child';
	'landscape_with_ruins';
	'the_sorceress';
	'dead_christ_mourned';
	'still_life_with_crab' ...
	};

files = { ...
	'01_1.jpg', '01_2.jpg', '01_3.jpg';
	'02_1.jpg', '02_2.jpg', '02_3.jpg';
	'03_1.jpg', '03_2.jpg', '03_3.jpg';
	'04_1.jpg', '04_2.jpg', '04_3.jpg';
	'05_1.jpg', '05_2.jpg', '05_3.jpg';
	'06_1.jpg', '06_2.jpg', '06_3.jpg';
	'07_1.jpg', '07_2.jpg', '07_3.jpg';
	'08_1.jpg', '08_2.jpg', '08_3.jpg';
	'09_1.jpg', '09_2.jpg', '09_3.jpg';
	'10_1.jpg', '10_2.jpg', '10_3.jpg';
	'11_1.jpg', '11_2.jpg', '11_3.jpg';
	'12_1.jpg', '12_2.jpg', '12_3.jpg';
	'13_1.jpg', '13_2.jpg', '13_3.jpg';
	'14_1.jpg', '14_2.jpg', '14_3.jpg';
	'15_1.jpg', '15_2.jpg', '15_3.jpg';
	'16_1.jpg', '16_2.jpg', '16_3.jpg';
	'17_1.jpg', '17_2.jpg', '17_3.jpg';
	'18_1.jpg', '18_2.jpg', '18_3.jpg';
	'19_1.jpg', '19_2.jpg', '19_3.jpg';
	'20_1.jpg', '20_2.jpg', '20_3.jpg';
	'21_1.jpg', '21_2.jpg', '21_3.jpg';
	'22_1.jpg', '22_2.jpg', '22_3.jpg';
	'23_1.jpg', '23_2.jpg', '23_3.jpg';
	'24_1.jpg', '24_2.jpg', '24_3.jpg';
	'25_1.jpg', '25_2.jpg', '25_3.jpg';
	'26_1.jpg', '26_2.jpg', '26_3.jpg';
	'27_1.jpg', '27_2.jpg', '27_3.jpg';
	'28_1.jpg', '28_2.jpg', '28_3.jpg';
	'29_1.jpg', '29_2.jpg', '29_3.jpg';
	'30_1.jpg', '30_2.jpg', '30_3.jpg';
	'31_1.jpg', '31_2.jpg', '31_3.jpg';
	'32_1.jpg', '32_2.jpg', '32_3.jpg';
	'33_1.jpg', '33_2.jpg', '33_3.jpg';
	};
%%

clc
close all

for i = 1:1
    a=cell2mat(files(i));
    ab=imread(a);
    ff(ab);
end

%img01_1 = imread('%',files(1));
%%%... figure, imshow(img01_1);




%ff(img01_1);

function [r] = ff(img01_1)
% rgb to hsv
img01_1 = histeq(img01_1);
img01_1_hsv = rgb2hsv(img01_1); 

img01_1_gray = rgb2gray(img01_1);

% background is black with a bit of noise
img01_1_hsv_s = img01_1_hsv(:,:,2); 
%%%... figure, imshow(img01_1_hsv_s), title('2'); 
%img01_1_hsv_s = imgaussfilt(img01_1_hsv_s, 2);

% filter to remove noise. 
filtered = medfilt2(img01_1_hsv_s, [7 7]);
%%%... figure, imshow(filtered), title('filtered');

% sharpening filter before threshold
sharpened = imsharpen(filtered, 'Threshold', 0.7);


% threshold is normalized to the range [0 1]
level = graythresh(sharpened);
BW = imbinarize(sharpened, level);
%%%... figure, imshow(BW), title('BW'); 

% fill the holes
BW_fill = imfill(BW, 'holes');
%%%... figure, imshow(BW_fill), title('BW_fill'); 

% measures binary images
%sArea = regionprops(BW_fill, 'Area');
%sBound = regionprops(BW_fill, 'BoundingBox');
%sCentroid = regionprops(BW_fill, 'Centroid');
sFilledImg = regionprops(BW_fill, 'FilledImage');
sFilledArea = regionprops(BW_fill, 'FilledArea');

% find binary painting 
sFilledArea_cell = struct2cell(sFilledArea);
sFilledArea_mat = cell2mat(sFilledArea_cell);
[max_num, max_ind] = max(sFilledArea_mat(:));
BW_img = sFilledImg(max_ind).FilledImage;
%%%... figure, imshow(BW_img);

uint8Image = uint8(255 * BW_img);
figure, imshow(uint8Image);
%c = normxcorr2(uint8Image,img01_1_gray);
%figure, surf(c), shading flat
%[ypeak, xpeak] = find(c==max(c(:)));
%yoffset = ypeak-size(BW_img,1);
%xoffset = xpeak-size(BW_img,2);

%figure, imshow(img01_1_gray);
%imrect(gca, [xoffset+1, yoffset+1, size(BW_img,2), size(BW_img,1)]);
end