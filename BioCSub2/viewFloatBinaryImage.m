function outmat = viewFloatBinaryImage(infile,rows,cols);
% Matlab script to read in images from float binary format.
% Parameters:
	infile = 'DILATIONresults.bin';
	rows  = 304;
	cols  = 304;
% 8-2-98 GSTEVENS

fp = fopen(infile,'r');
[tmp,count] = fread(fp,'float32');
% Check file size
if count ~= (rows*cols)
  'Inconsistent datafile size; check parameters'
  %stop
end

outmat=zeros(rows,cols);
  for rCnt = 1:rows
    outmat(rCnt,:) = tmp((rCnt-1)*cols+1:rCnt*cols)';
  end

fclose(fp);
imagesc(outmat); colormap(gray); axis image; axis off;
clear tmp
