%% script to generate .bio file for SDBIO from SIMM
% first run a modified dynamics pipeline simulation with output files
% dofs.txt, zerolength.txt and momentarms.txt
% These files should be saved in the /model directory
% This is where the .bio file will be written too

dir_file = mfilename('fullpath');   % directory where sdbio tools are stored
index = findstr(dir_file, 'sdbio\'); % find where 'sdbio/' part of the directory starts
path = sscanf(dir_file, '%c', index-1);  % store the directory up to that character

% choose model
modelname = 'das3';

% generate config file from SIMM output file dofs.txt
% if (mot2cfg(path, modelname))
%     disp('error in mot2cfg file');
%     return;
% end

% if model is das2 or higher, generate GH config file from SIMM output file dofs.txt
% if strcmp(modelname,'das2')||strcmp(modelname,'das3')
%     if (mot2cfg_GH(path, modelname))
%         disp('error in mot2cfg_GH file');
%         return;
%     end
% end

% if model is das3, generate scapula config file from SIMM output file dofs.txt
% if strcmp(modelname,'das3')
%     if (mot2cfg_scap(path, modelname))
%         disp('error in mot2cfg_scap file');
%         return;
%     end
% end

% compute polynomials for muscle-tendon length from SIMM output files
% dofs.txt, zerolength.txt, momentarms.mot and config file
% store them in poly_results.txt
% if (pathpo4(path, modelname))
%     disp('error in pathpo4 file');
%     return;
% end

% for DAS2 or DAS3:
% compute polynomials for GH force vectors from SIMM output files
% dofs.txt, zerolength.txt, GH_fvectors.mot and GH config file
% store them in poly_results_GH.txt
% if strcmp(modelname,'das2')||strcmp(modelname,'das3')
%     if (pathpo_GH(path, modelname))
%         disp('error in pathpo_GH file');
%         return;
%     end
% end

% for DAS3:
% compute polynomials for scapula force vectors from SIMM output files
% dofs.txt, zerolength.txt, scap_fvectors.mot and scapula config file
% store them in poly_results_scap.txt
% if strcmp(modelname,'das3')
%     if (pathpo_scap(path, modelname))
%         disp('error in pathpo_GH file');
%         return;
%     end
% end

% generate .bio file for sdbio from poly_results.txt, poly_results_GH.txt, 
% poly_results_scap.txt, dofs.txt and the SIMM muscle file
if (makebio(path, modelname))
    disp('error in makebio file');
    return;
end
