input = load('input.txt');
c_output = importdata('c_output.txt');
c_output = cell2mat(c_output);
c_output = str2num(c_output);
Fs = 256;
L = 256;
f = Fs*(0:(L/2))/L;
Y = fft(input);
P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
%P1(1:10) = 0;

% plot(Y);
plot(f,P1);
hold on
P2 = abs(c_output/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
plot(f,P1);
%plot(c_output);
% title('Single-Sided Amplitude Spectrum of S(t)')
% xlabel('f (Hz)')
hold off

% %下面是关于位移fft算法直接图像变化程序
% for i = 1:(2048 - 128)
%     Y_Loop = fft(input(i:i + 128));
%     P2 = abs(Y_Loop/L);
%     P1 = P2(1:L/2+1);
%     P1(2:end-1) = 2*P1(2:end-1);
%     figure(1)
%     plot(Y_Loop)
%     axis([-15000 15000 -15000 15000]);
%     figure(2)
%     plot(f,P1);
%     axis([0 60 0 120]);
%     pause(0.05);
% end

