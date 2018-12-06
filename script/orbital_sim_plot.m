clear all; close all;
A = importdata('results/trajectory/satellites.txt');
G = importdata('results/trajectory/groundstation.txt');

save_video = false;
draw_earth = true;

if(draw_earth)
  r = 6200000;

  [X,Y,Z] = sphere(100);
  x = [X(:); X(:); X(:)] .* r;
  y = [Y(:); Y(:); Y(:)] .* r;
  z = [Z(:); Z(:); Z(:)] .* r;
end

for n = 1 : length(A)
    o = [0,0,0];
    v = A(n,:);
    u = G(n,:);
    scatter3(o(1), o(2), o(3), 'filled');
    hold on;
    scatter3(v(:,1:3:end), v(:,2:3:end), v(:,3:3:end), 'filled');
    scatter3(u(:,1:3:end), u(:,2:3:end), u(:,3:3:end), [], [0 1 1; 0 1 1], 'filled');

    if(draw_earth)
      scatter3(x, y, z);
    end

    hold off;

    if(save_video)
      F(n) = getframe(gcf);
    end

    % To set a view for the simulation, uncomment the line below
    view(0,45);
    xlim([-10000000 10000000]);
    ylim([-10000000 10000000]);
    zlim([-10000000 10000000]);
    drawnow
end

if(save_video)
  writerObj = VideoWriter('oribtal_sim.avi');
  writerObj.FrameRate = 30;
  open(writerObj);

  for i = 1 : length(F)
    frame = F(i);
    writeVideo(writerObj, frame);
  end

  close(writerObj);
end
