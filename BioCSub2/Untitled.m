fp = fopen('test_image1.bin');
img = fread(fp,[304 304],'float','b');
imgread(img);