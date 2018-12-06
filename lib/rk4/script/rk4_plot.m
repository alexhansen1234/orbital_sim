clear all; close all;
A = importdata('results.txt');

for n = 1 : length(A)
    v = [0,0,0];
    v = [v; A(n,:)];
    scatter3(v(:,1), v(:,2), v(:,3));
    xlim([-10000000 10000000]);
    ylim([-10000000 10000000]);
    view(0, 90);
    drawnow
end