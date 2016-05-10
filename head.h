% filename 
filename = 'KF05_LAENGS.mpf';
%filename = 'KF05_QUER.mpf'

% Read MATLAB file into cell array of strings
number_rows = length(textread(filename, '%s', 'delimiter', '\n')) 

values = zeros(number_rows, 4); %Array [X Y Z] initilization


fid = fopen(filename); % Datei ï¿½ffnen
iLine = 1; %Laufvariable zum Zï¿½hlen der Zeilen
tline = fgetl(fid); % Zeile aus NC-Datei auslesen
while ischar(tline) %Fortsetzen bis Ende der Datei erreicht
    if(tline(1) == ';')
		%Bei Kommentarzeile kann sofort abgebrochen werden.
        tline = fgetl(fid); %nï¿½chste Zeile lesen
        continue; %Abbruch
    end
    tline_split = regexp(tline, ' ', 'split');%gelesene Zeile in Einzelanweisungen aufteilen (Trennzeichen ' ')
    
	%Initialisierung der Positionswerte
    Xval = NaN; 
    Yval = NaN;
    Zval = NaN;
    Gval = NaN;
%     Aval = NaN;
%     Bval = NaN;
%     Cval = NaN;
%     Fval = NaN;
    
    for iB = 1:size(tline_split, 2) %Alle Anweisungen durchgehen
       block = tline_split{1,iB}; %Anweisung auslesen
       firstchar = block(1); %Ersten Buchstaben bestimmen
       switch firstchar %Anweisung prï¿½fen
           case 'N'
				%Zeilenanzahl, kann einfach ï¿½bersprungen werden
           case ';'
%              %Bei Beginn eines Kommentars kann zur nï¿½chsten Zeile gesprungen werden
               break;
           case 'X'
               Xval = str2double(block(2:end)); %Wert z nach Anweisung auslesen (Xzzzz.zzz)
           case 'Y'
               Yval = str2double(block(2:end)); %Wert z nach Anweisung auslesen (Yzzzz.zzz)
           case 'Z'
               Zval = str2double(block(2:end)); %Wert x nach Anweisung auslesen (Zxxxx.xxx)
           case 'G'
               Gval = str2double(block(2:end)); %Wert x nach Anweisung auslesen (Zxxxx.xxx)
%            case 'A'
%                Aval = str2double(block(2:end));    
%            case 'B'
%                Bval = str2double(block(2:end));
%            case 'C'
%                Cval = str2double(block(2:end));
%            case 'F'
%                Fval = str2double(block(2:end));
           otherwise
%                %Verhalten bei unbekannten Anweisungen festlegen
       end
    end
    
    %  example : isnan([pi NaN Inf -Inf]) is [0 1 0 0]
    if(~all(isnan([Xval, Yval, Zval]))) 
        if(isnan(Xval) && iLine>1)
            Xval = values(iLine-1, 1);
        end
        if(isnan(Yval) && iLine>1)
            Yval = values(iLine-1, 2);
        end
        if(isnan(Zval) && iLine>1)
            Zval = values(iLine-1, 3);
        end
%         if(isnan(Bval) && iLine>1)
%             Bval = values(iLine-1, 4);
%         end
%         if(isnan(Cval) && iLine>1)
%             Cval = values(iLine-1, 5);
%         end
%         if(isnan(Fval) && iLine>1)
%             Fval = values(iLine-1, 6);
%         end
    end
    
%   values(iLine, :) = [Xval, Yval, Zval, Bval, Cval, Fval];
    values(iLine, :) = [Xval, Yval, Zval,Gval,iLine];
    
    tline = fgetl(fid);
    iLine = iLine+1;
end

fclose(fid);

%values(all(isnan(values),2), :) = []; % Wenn alle Werte NaN --> Zeile lï¿½schen
%values(values>98) = 0; % zu groï¿½e Werte fï¿½r Anzeige entfernen
%figure %neue Grafik
%plot3(values(:,1), values(:,2), values(:,3)); %Ausgabe
%axis image %Seitenverhï¿½ltnis
