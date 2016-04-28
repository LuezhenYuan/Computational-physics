# Procude gif in Matlab

```{matlab}
data=dlmread('result.txt','\t',1,0);
figure(1)
axis off
box off
filename = 'Thermal_Conduction.gif';
hold on
for j=0:35
for i=1:11
plot(data(i+11*j,1),1,'s','MarkerFaceColor',[data(i+11*j,3),0,1-data(i+11*j,3)],'MarkerEdgeColor',[data(i+11*j,3),0,1-data(i+11*j,3)],'MarkerSize',45)
end
frame = getframe(1);
im = frame2im(frame);
[imind,cm] = rgb2ind(im,256);
if j == 0;
    imwrite(imind,cm,filename,'gif', 'Loopcount',inf);
else
    imwrite(imind,cm,filename,'gif','WriteMode','append');
end
%text(8,1.05,'time')
%text(9,1.05,num2str(j))
pause(0.05)
end
```

# include gif in pdf report(Need support from your pdf reader)
```{bash}
mkdir gif
cp Thermal_Conduction.gif gif/
cd gif
convert Thermal_Conduction.gif -coalesce Thermal_Conduction_%d.pdf
```
