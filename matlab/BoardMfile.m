clc;
d = imread('stage.bmp');
s = '';
size = 0;
count =1;

% for i=1:240
%    for j=1:240
%        if j == 1 
%         s = strcat(s,(num2str(d(i,j))));
%        else
%         s = strcat(s,',',(num2str(d(i,j))));
%        end
%    end
%    s = strcat('{',s,'},');
%    disp(s);
%    s = '';
% end



filename_1 = 'InitialBoard2.txt';
file_1 = fullfile('C:','Users','andreas','Desktop','pacman','matlab',filename_1);
fileID_1 = fopen(file_1,'r');
if ( fileID_1==-1 )
    error('cannot open file',file_1);
end
 
B = zeros(240,240);
formatSpec='%d %d'
sizeB=[240 Inf];
B = fscanf(fileID_1,formatSpec,sizeB);


fclose(fileID_1);

for i=181:240
   for j=1:60
       if ( B(i,j)~=0) 
        size = size + 1 ;
       end
   end
end

 A= zeros(2,size);

for i=181:240
   for j=1:60
       if ( B(i,j)~=0 ) 
        A(1,count) = j;
        A(2,count) = i;
          count = count +1;
       end
   end
end


filename_2 = 'myfile.txt';
file_2 = fullfile('C:','Users','andreas','Desktop','pacman','matlab',filename_2);
fileID_2 = fopen(file_2,'w');
if ( fileID_2 ==-1 )
    error('cannot open file',file_2);
end


for i=1:2
   for j=1:size
       if j == 1 
        s = strcat(s,(num2str(A(i,j))));
       else
        s = strcat(s,',',(num2str(A(i,j))));
       end
   end
   s = strcat('{',s,'},');
   fprintf(fileID_2,s);

   disp(s);
   s = '';
end

fclose(fileID_2);



