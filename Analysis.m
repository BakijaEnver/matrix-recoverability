primes = [2,3,5,7,11,13,17,19,23,29, 31];
resultGF = [];

for k = primes

  
    m = 4;
    n = 4;
    d = 5;
    corrected = 0;
    samples = 100000;
    
    command = sprintf('./bipartite %d %d %d %d %d %d', m, n, d, k, corrected, samples);
    system(command);
    
    filename = 'matrices/original.txt';
    A = readmatrix(filename);

    C = zeros(1,max(m,n));

    for i = 1:samples
        matrix = A(((i-1)*m+1):i*m,1:n);
        c = gfrank(matrix, k);       
        
        determinant = rem(int16(det(matrix)),k);
        if determinant == 0
            if c == n
                determinant
                c
                matrix
                break
            end
        end
    end
    k
    delete('matrices/original.txt');
    
    resultGF = [resultGF, C(max(m,n)) / samples];
    

    
end
