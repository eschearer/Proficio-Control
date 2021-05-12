function out = inject_test(in,extra,index)
% adds an EXTRA signal to specified elements (INDEX) of the IN vector

out = in;
for i=index
    out(i)=in(i)+extra;
end