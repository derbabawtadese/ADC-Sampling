function ADC_FFT_Serial_Port

    SerialInput = serialport("COM3",230400,"Timeout",30);
    
    M = 4096;
    N = M/2;
    data = read(SerialInput, M, "uint8");
    Data = double(zeros(1,N));
    
    j=1;
    for i=1:2:M
            Data(j) =  (bitshift( data(i),8) + data(i+1))*0.0008; %LSB+MSB
            j = j + 1;
    end

    Fs = 200;
    time = (0:N-1)./Fs;
    freq = [0:N/2-1,-N/2:-1].*(Fs/N);
    figure(1),stem(time, Data,'-o', 'g')
    xlabel('Time (s)')
    ylabel('Amplitude')

    Data = fft(Data);
    figure(2), stem(freq(1:N/2),20*log10(abs(Data(1:N/2))), 'r')
    xlabel('Frequency (Hz)')
    ylabel('Spectral Magnitude (dB)')
    shg
end
