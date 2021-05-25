primes = [2,3,5,7,11,13,17,19,23,29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71];
resultGF = [];

for k = primes

    
    m = 10;
    n = 10;
    d = 4;
    corrected = 0;
    samples = 100000;
    
    command = sprintf('./bipartiteFull %d %d %d %d %d %d', m, n, d, k, corrected, samples);
    system(command);
    
    filename = 'matrices/original.txt';
    A = readmatrix(filename);

    C = 0;

    for i = 1:samples
        matrix = A(((i-1)*m+1):i*m,1:n);
        determinant = rem(int16(det(matrix)),k);
        if determinant ~= 0
            C = C + 1;
        end
    end
    k
    delete('matrices/original.txt');
    
    resultGF = [resultGF, C / samples];
    

    
end
