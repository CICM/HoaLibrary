anglesDegreeHoraire = (0:71)*5;
anglesTrigo = zeros(1,72);


for i = 1:72
    anglesTrigo(1,i) = -anglesDegreeHoraire(1,i) + 360;
    anglesTrigo(1,i) = anglesTrigo(1,i) + 90;
    if(anglesTrigo(1,i) >= 360)
        anglesTrigo(1,i) = anglesTrigo(1,i) - 360;
    elseif (anglesTrigo(1,i) < 0)
        anglesTrigo(1,i) = anglesTrigo(1,i) + 360;
    end
            strcat('left', sprintf('%d', anglesTrigo(1,i)))
end


 for i = 1:72 
     wavwrite( left(1:200,i), 44100, 16, strcat('left' , sprintf('%d', anglesTrigo(1,i))))
     wavwrite(right(1:200,i), 44100, 16, strcat('right', sprintf('%d', anglesTrigo(1,i))))
 end




