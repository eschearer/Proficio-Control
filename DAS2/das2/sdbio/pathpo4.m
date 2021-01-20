function error = pathpo4(path, modelname)

% pathpoly.m
%
% Computes best fitting polynomial for muscle-tendon length L as a function
% of kinematic degrees of freedom q.
%
% This is done from moment arms generated by SIMM, using the relationship
%   (momentarm of muscle m with respect to dof q) = dLm/dq
%
% changed by Dimitra Blana - 2/26/07
% 1. write all polynomials to one file (poly_results.txt) instead of one file per
%    muscle
% 2. changed how the header lines in SIMM motion file are skipped
%    (instead of specific number, the keyword "endheader" is found)
% 3. changed directory where files are read and written to depend on the
%    model chosen (das2 at the moment)
% 4. all moment arms are read from one SIMM motion file into matrix momarms
% 5. the musculotendon length at zero position of model is also read from a
%    SIMM output file, zerolength.txt
% 6. stopping criteria: either error < 10% of maximum moment arm, or change
%    in error < 5% of error 

%% setup directories and open files

format long;			% so we get full precision output for polynomial coefficients

% this is where pathpoly.cfg is
% and where data files for this model will be stored
folder = [path modelname '/model'];

% config file (input)
fullpath = [folder '/pathpoly.cfg'];
configfile = fopen(fullpath,'r');
if (configfile < 0)
    fprintf('Error: could not open %s\n', fullpath);
    fclose('all');
    error = 1;
    return;
end

% log file (output)
fullpath = [folder '/pathpoly.log'];
logfile = fopen(fullpath,'w');
if (logfile < 0)
    fprintf('Error: could not open %s\n', fullpath);
    fclose('all');
    error = 1;
    return;
end

% results file (output)
fullpath = [folder '/poly_results.txt'];
polyfile = fopen(fullpath,'w');
if (polyfile < 0)
    fprintf('Error: could not open %s\n', fullpath);
    fclose('all');
    error = 1;
    return;
end

% zero length file (input)
fullpath = [folder '/zerolength.txt'];
lengthfile = fopen(fullpath,'r');
if (lengthfile < 0)
    fprintf('Error: could not open %s\n', fullpath);
    fclose('all');
    error = 1;
    return;
end

%% get moment arms out of SIMM motion file
% SIMM motion file where moment arms are stored
% this is written on the third line of the config file
fgets(configfile);
fgets(configfile);
filename = fgetl(configfile);
fseek(configfile, 0, 'bof'); % reposition the file identifier to the beginning of the config file

fullpath = [folder '/' filename];
momarmfile = fopen(fullpath,'r');
if (momarmfile < 0)
    fprintf('Error: could not open %s\n', fullpath);
    fclose('all');
    error = 1;
    return;
end

% get number of columns from the line: 'datacolumns <>'
line = fgetl(momarmfile);
while (not(strncmp(line, 'datacolumns', 11)))
    line = fgetl(momarmfile);
end
num_col = sscanf(line, '%*s%i');

% skip rest of header: look for keyword 'endheader' and skip 2 more lines after that
line = fgetl(momarmfile);
while (not(strcmp(line, 'endheader')))
    line = fgetl(momarmfile);
end
fgetl(momarmfile); % empty line after end of header
fgetl(momarmfile); % line with names of DOFs and momentarms

% put all the moment arm data in matrix momarms
momarms = fscanf(momarmfile,'%f',[num_col,inf]); % it reads in column order
momarms = momarms';
num_data = size(momarms,1);
fclose(momarmfile);

%% main loop for each muscle element
while 1

    % read next muscle name from config file
    musclename = fgets(configfile);
    s = fgets(configfile);
    if s<=0, break, end		% quit if end of config file is reached
    musclename = strtrim(musclename);
    d = sscanf(s,'%d');

    % read number of dofs spanned by this muscle, and which polynomial order requested
    ndofs = d(1,1);
    order = d(2,1);

    % count how many parameters the polynomial model for muscle length has
    npar = prod(1:ndofs+order)/prod(1:ndofs)/prod(1:order);
    fprintf(1,'Muscle name:      %s\n',musclename);
    fprintf(1,'Number of DOFs:   %d\n',ndofs);
    fprintf(1,'Polynomial order: %d\n',order);
    fprintf(1,'Potential number of polynomial terms: %d\n',npar);
    tot_data = num_data*ndofs;	% total number of data points
    A = zeros(tot_data, npar);	% allocate memory space for A
    b = zeros(tot_data, 1);		% allocate memory space for b

    % get zero musculotendon length for this muscle from file
    % zerolenght.txt
    tline = fgetl(lengthfile);
    % skip possible comments
    while (strncmp(tline, '#', 1))
        tline = fgetl(lengthfile);
    end
    if (not(strcmp(sscanf(tline,'%s',1),musclename)))
        fprintf('Error: could not find zero length of %s\n', musclename);
        fclose('all');
        error = 1;
        return;
    end
    mus_length = sscanf(tline, '%*s%f');

    % moment arm data for this muscle comes from ndofs files, with names listed on config.txt
    for i = 1:ndofs
        % read from config file the filename and column numbers where data can be found
        filename = fgetl(configfile);  % this is not used here anymore (see comment in start of file)
        s = fgetl(configfile);
        if s<=0, break, end		% quit if end of config.txt is reached
        r = sscanf(s,'%d');
        mcol = r(1);
        acol = r(2:ndofs+1);

        % read data from momarms matrix
        % take moment arm and angles from the right columns
        b((i-1)*num_data+1:i*num_data) = momarms(:,mcol);
        ang = (momarms(:,acol) + 1e-6) * pi/180;	% convert to radians and protect against angle = 0.0

        % generate the npar polynomial terms, and for each term, add a column to A
        polylist = zeros(npar,ndofs);
        expon = zeros(num_data,ndofs);	% start with all exponents zero
        for ii=1:npar
            polylist(ii,:) = expon(1,:);
            A((i-1)*num_data+1:i*num_data,ii) = expon(:,i).*prod(ang.^expon,2)./ang(:,i); % contribution of this term to moment arm i
            % generate the next set of exponents, but remain within model order
            k = 1;
            while (1)
                expon(:,k) = expon(:,k)+1;
                if (sum(expon(1,:)) > order && ii<npar)
                    expon(:,k)=0;
                    k = k+1;
                else
                    break;
                end
            end
        end     % done generating model terms
    end		% done reading all data files for this muscle
    fprintf('Total number of data points: %d\n',tot_data);

    % now we have all data for this muscle stored in A and b
    % remove from A the first column (constant term of polynomial)
    A = A(:,2:npar);
    polylist = polylist(2:npar,:);
    b = -b;	% this is because moment arms on SIMM output are -dL/dq

    maxmomarm = max(abs(b))*1000; % maximum moment arm (in mm) for the muscle and dof

    % solve the full model with npar-1 terms
    p = A\b;		% compute coefficients of the best fitting model
    bpred = A*p;	% these are the moment arms predicted by this model
    res = bpred-b;	% residuals
    RMSfull = (sqrt(sum(res.^2)/tot_data)) * 1000;		% RMS of residuals, in mm
    fprintf('RMS fit error of the full model is: %f mm\n',RMSfull);
    fprintf('maximum moment arm: %f mm\n',maxmomarm);
    fprintf(logfile,'%s\n',musclename);
    fprintf(logfile,'  RMS fit error of the full model is: %f mm\n',RMSfull);
    fprintf(logfile,'  maximum moment arm: %f mm\n',maxmomarm);

    % now do stepwise regression to select polynomial terms for a smaller model
    Aselected = [];
    polylist_selected = [];
    npar_selected = 0;
    % outer loop: successively add columns to Aselected
    for i = 1:npar-1
        [nrows, ncolumns] = size(A);
        % inner loop: find the column of A that causes most reduction in RMS when added to Aselected
        RMSnew = zeros(1,ncolumns); % this will store the RMS errors of each expanded model
        for j = 1:ncolumns
            % add column j from A to Anew
            Anew = [Aselected A(:,j)];
            % solve new p's
            pnew = Anew\b;
            % compute new RMS fit error
            RMSnew(j) = (norm(Anew*pnew - b)/(sqrt(tot_data))) * 1000; 	% convert to mm
        end
        % now determine which expanded model had the lowest RMS
        [RMSmin, col] = min(RMSnew);
        % if the change in error is less than 5%, stop without adding this term
        if ((i>1)&&((RMS - RMSmin)/RMS<0.05))
            fprintf('Change in error: %3f. No more terms added.\n ',(RMS - RMSmin)/RMS);
            fprintf(logfile,'Change in error: %3f. No more terms added.\n ',(RMS - RMSmin)/RMS);
            break;
        end
        % otherwise add this column to Aselected
        Aselected = [Aselected A(:,col)];npar_selected = npar_selected + 1;
        p = Aselected\b;		% solve the coefficients (again)
        % compute some error measures
        SSE = sum((Aselected*p-b).^2); 			% summed squared errors (SSE)
        RMS = (sqrt(SSE/tot_data)) * 1000; 			% RMS error, is the same as what we had before
        GCV = SSE/((num_data - npar_selected)^2);    	% Generalized Cross Validation
        AIC = log(SSE) + 2*npar_selected/tot_data;   	% Akaike's Information Criterion
        % print what we just did, on screen and on output file
        fprintf('Model addition step %3i: Added term ',i);
        fprintf('%i ',polylist(col,:));
        fprintf('-- RMS=%6.2f, GCV=%8.3e, AIC = %6.2f\n',RMS,GCV,AIC);
        fprintf(logfile,'  Model addition step %3i: Added term ',i);
        fprintf(logfile,'%i ',polylist(col,:));
        fprintf(logfile,'-- RMS=%f, GCV=%e, AIC = %f\n',RMS,GCV,AIC);

        % remember the exponents of this polynomial term
        polylist_selected = [polylist_selected ; polylist(col,:)];
        % remove this column from A and from polylist so it is not used again
        A = [A(:,1:(col-1)) A(:,(col+1):ncolumns)];
        polylist = [polylist(1:(col-1),:);polylist((col+1):ncolumns,:)];
        % stop adding terms if RMS error in fvectors is less than 10% of max
        if (RMS<=0.1*maxmomarm)
            break;
        end
    end 		% and go find the next term

    % make plots, use config.txt to control how the plots are made

    %.. to be done ..

    % write this muscle's model on the output file
    fprintf(polyfile,musclename);
    fprintf(polyfile,'\nparameters %d\n',npar_selected+1);
    fprintf(polyfile,'# exponents ... coefficient\n');
    fprintf(polyfile,'\t');
    fprintf(polyfile,'%3d ',zeros(1,ndofs));		% write the line for the contant term of polynomial
    fprintf(polyfile,'   %10.5e \n',mus_length);
    for i = 1:npar_selected
        fprintf(polyfile,'\t');
        fprintf(polyfile,'%3d ',polylist_selected(i,:));
        fprintf(polyfile,'   %10.5e \n', p(i));
    end
    fprintf(logfile,'  %d polynomial terms were written for %s\n',npar_selected+1, musclename);
end 		% go process next muscle

fclose(configfile);
fclose(polyfile);
fclose(lengthfile);
fclose(logfile);
error = 0;