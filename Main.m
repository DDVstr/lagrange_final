clear,clc, close all;

fprintf('Начало программы.\n');

fileNameSrcY = 'SrcY.bin';
fileNameSrcYTrue = 'SrcYTrue.bin';
fileNameInterpY = 'InterpY.bin';

Dx = 0.25;

fileSrcY = fopen('SrcY.bin', 'rb');
SrcY = fread(fileSrcY, 'double');
fclose(fileSrcY);

fileSrcYTrue = fopen(fileNameSrcYTrue, 'rb');
SrcYTrue = fread(fileSrcYTrue, 'double');
fclose(fileSrcYTrue);

fileInterpY = fopen(fileNameInterpY, 'rb');
InterpY = fread(fileInterpY, 'double');
fclose(fileInterpY);

figure;
plot((1:length(SrcY)) + Dx, SrcY, 'o', 1:length(SrcYTrue), SrcYTrue, '--s', 1:length(InterpY), InterpY, '-.*'); grid on ;grid minor;
xlabel('index, $$i$$', 'Interpreter', 'latex', 'FontSize', 14);
ylabel('$$Y_{i}$$', 'Interpreter', 'latex', 'FontSize', 14);
legend({'Source Y for interpolation', 'Source Y in point of interpolation', 'Interpolated Y'}, 'Interpreter', 'latex', 'FontSize', 10);

fprintf('Программа завершена.\n');