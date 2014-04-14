% Fonction fuzzy avec comme paramètres N, le nombre de MFs, regle, la matrice des règles
% A et B les deux entrées avec leurs bornes et leurs échelles respectives

function [centro] = fuzzy_speed (N,regle,A,A_min,A_max,A_scale,B,B_min,B_max,B_scale)

% Test de l'échelle et calcul du pourcentage de chaque entrée
if strcmp(A_scale,'log')
    A_pourc = (log(A)-log(A_min))/(log(A_max)-log(A_min));
else
    A_pourc = (A-A_min)/(A_max-A_min);
end

if strcmp(B_scale,'log')
    B_pourc = (log(B)-log(B_min))/(log(B_max)-log(B_min));
else
    B_pourc = (B-B_min)/(B_max-B_min);
end

x_tri = zeros(1,N+2);

MF_A = zeros(1,2);
MF_B = zeros(1,2);

% Calcul des points des MFs et enregistrement dans x_tri
for i=1:N+2
    x_tri(i)=(i-2)/(N-1);
end

1-2/3-1 = -0.5
2-2/3-1 = 0
3-2/3-1 = 0.5
4-2/3-1 = 1
5-2/3-1 = 1.5

% Test des MFs concernées et enregistrement dans MF[2]
n=0;
m=0;
for i=1:N
    if A_pourc > x_tri(i) && A_pourc < x_tri(i+2)
        n = n+1;
        MF_A(n)=i;
    end
    if B_pourc > x_tri(i) && B_pourc < x_tri(i+2)
        m = m+1;
        MF_B(m)=i;
    end
end

% Calcul des différentes fonctions de sortie
out_x = zeros((n*m),4);
out_y = zeros((n*m),4);

count = 0;

for i=1:m
    for j=1:n
        count=count+1;
        % Calcul du segment x entre MF et le point
        partA_x = min(A_pourc-x_tri(MF_A(j)),x_tri(MF_A(j)+2)-A_pourc);
        partB_x = min(B_pourc-x_tri(MF_B(i)),x_tri(MF_B(i)+2)-B_pourc);
        % Calcul des 4 points x pour chaque MF de sortie
        out_x(count,:)=[max(x_tri(regle(MF_B(i),MF_A(j))),0) max((x_tri(regle(MF_B(i),MF_A(j)))+min(partA_x,partB_x)),0) min((x_tri(regle(MF_B(i),MF_A(j))+2)-min(partA_x,partB_x)),1) min(x_tri(regle(MF_B(i),MF_A(j))+2),1)];
        % Calcul de la valeur y associée au point x à travers la fonction triangle
        if out_x(count,2)==0
            Coo_x = -out_x(count,3);
        else
            Coo_x = out_x(count,2);
        end
        A = x_tri(regle(MF_B(i),MF_A(j)));
        B = x_tri(regle(MF_B(i),MF_A(j))+1);
        out_y(count,2) = (Coo_x-A)/(B-A);
        % Toutes les valeurs y = 0 sauf 2 (ou 1 si triangle plein)
        out_y(count,3) = out_y(count,2);
    end
end

for i=1:count
    signalx_pre = -1;
    numb(i) = 0;
    for j=1:4
        if out_x(i,j) == signalx_pre
            signaly(i,numb(i)) = max(signaly(i,numb(i)),out_y(i,j));
        else
            numb(i) = numb(i) + 1;
            signalx(i,numb(i)) = out_x(i,j);
            signaly(i,numb(i)) = out_y(i,j);
            signalx_pre = out_x(i,j);
        end
    end
end

% Boucle permettant de faire le max entre tous les points des différentes fonctions de sortie
l = 1;
cond = 0;
tst = 0;
minx=1.1;
for i=1:count
    xi(i) = 1;
    cond = cond + numb(i) +1;
    minx = min(minx,signalx(i,xi(i)));
end
signalfinalx(1)=minx;

while cond~=tst
    tst = 0;
    minx=1.1;
    for i=1:count
        tst = tst + xi(i);
        if xi(i)<=numb(i)
            minx = min(minx,signalx(i,xi(i)));
        end
    end

    for i=1:count
        if xi(i)<=numb(i) && minx == signalx(i,xi(i))
            xi(i) = xi(i) + 1;
        end
    end

    if signalfinalx(l) ~= minx && minx~=1.1
        l = l + 1;
        signalfinalx(l) = minx;
    end
end

for i=1:count
    ind(i)=1;
    for j=1:l
        if ind(i)>numb(i)
            signalycalc(i,j)=0;
        elseif signalfinalx(j)==signalx(i,ind(i))
            signalycalc(i,j)=signaly(i,ind(i));
            ind(i) = ind(i) + 1;
        elseif signalfinalx(j)<signalx(i,1)
            signalycalc(i,j)=0;
        elseif signalfinalx(j)<signalx(i,ind(i))
            signalycalc(i,j) = signaly(i,ind(i)-1) + (signaly(i,ind(i))-signaly(i,ind(i)-1))/(signalx(i,ind(i))-signalx(i,ind(i)-1))*(signalfinalx(j)-signalx(i,ind(i)-1));
        elseif signalfinalx(j)>signalx(i,ind(i))
            ind(i) = ind(i) + 1;
            j=j-1;
        end
    end
end

for i=1:l
    maxy(i) = 0;
    for j=1:count
        maxy(i) = max(maxy(i),signalycalc(j,i));
    end
    signalfinaly(i)=maxy(i);
end

oki=0;
for i=1:l
    prob=0;
    for j=1:count
        if maxy(i) == signalycalc(j,i)
            prob = prob + 1;
            sigtmp(prob)=j;
        end
    end
    if prob==1
        sigpre(i) = sigtmp(1);
    else
        for p=1:prob
            if i == 1
                if maxy(2) == signalycalc(sigtmp(p),2)
                    sigpre(i) = sigtmp(p);
                    oki=1;
                elseif oki == 0 && p==prob
                    sigpre(i) = sigtmp(p);
                end
            elseif maxy(i-1) == signalycalc(sigtmp(p),i-1) || maxy(min(i+1,l)) == signalycalc(sigtmp(p),min(i+1,l))
                sigpre(i) = sigtmp(p);
            end
        end
    end
    if sigpre(i)==sigpre(max(i-1,1))
        corr(i)=0;
    else
        corr(i)=1;
    end
end

k=0;
for i=1:l
    if corr(i)==1
        k = k+1;
        alpha = (signalycalc(sigpre(i),i)-signalycalc(sigpre(i),i-1))/(signalfinalx(i)-signalfinalx(i-1));
        beta = (signalycalc(sigpre(i-1),i)-signalycalc(sigpre(i-1),i-1))/(signalfinalx(i)-signalfinalx(i-1));
        signalfcx(k)=(signalfinalx(i-1)*alpha - signalycalc(sigpre(i),i-1) - signalfinalx(i-1)*beta + signalycalc(sigpre(i-1),i-1))/(alpha-beta);
        signalfcy(k)= signalycalc(sigpre(i),i-1) + (signalfcx(k)-signalfinalx(i-1))*alpha;
        k = k+1;
        signalfcx(k)=signalfinalx(i);
        signalfcy(k)=signalfinaly(i);
    else
        k = k+1;
        signalfcx(k)=signalfinalx(i);
        signalfcy(k)=signalfinaly(i);
    end
end

signalfcxtmp=signalfcx;
signalfcytmp=signalfcy;
nbt=2;

for i=3:k
    nbt=nbt+1;
    if roundn(signalfcytmp(i),-4)==roundn(signalfcytmp(i-1),-4) && roundn(signalfcytmp(i-1),-4)==roundn(signalfcytmp(i-2),-4)
            signalfcx([nbt-1])=[];
            signalfcy([nbt-1])=[];
            nbt=nbt-1;
    end
end

% Calcul des aires sommées à chaque point x
aire = zeros(1,(nbt-1));
for i=1:(nbt-1)
    aire(1,i) = aire(1,max(i-1,1)) + (signalfcx(i+1)-signalfcx(i))*(signalfcy(i+1)+signalfcy(i))/2;
end
% Test pour déterminer les point x ou l'aire dépasse 50%
for pt=1:(nbt-1)
    if aire(1,pt)>(aire(1,(nbt-1))/2)
        break;
    end
end

% Calcul du poucentage d'aire du trapèze pour déterminer le centroide
if pt==1
    pourc = 0.5/((aire(1,pt))/aire(1,(nbt-1)));
else
    pourc = (0.5-(aire(1,pt-1)/aire(1,(nbt-1))))/((aire(1,pt)-aire(1,pt-1))/aire(1,(nbt-1)));
end
    
coeff_a = (signalfcy(pt+1)-signalfcy(pt))/(signalfcx(pt+1)-signalfcx(pt));

if roundn(coeff_a,-4) == 0
    centro=pourc*(signalfcx(pt+1)-signalfcx(pt))+signalfcx(pt);
else
    coeff_b = 2*signalfcy(pt);

    coeff_c = -pourc*(signalfcx(pt+1)-signalfcx(pt))*(signalfcy(pt)+signalfcy(pt+1));

    delta = coeff_b^2 - 4*coeff_a*coeff_c;

    centro1 = (-coeff_b-sqrt(delta))/(2*coeff_a) + signalfcx(pt);

    centro2 = (-coeff_b+sqrt(delta))/(2*coeff_a) + signalfcx(pt);
    
    if centro1 >= signalfcx(pt) && centro1 <= signalfcx(pt+1)
        centro = centro1;
    else
        centro = centro2;
    end
end

% Normalisation des bornes entre 0 et 1
norm = (2-sqrt(2))/(2*(N-1));

if centro <= 0.5
    centro = centro - norm*((0.5-centro)/(0.5-norm));
else
    centro = centro + norm*(1-(((1-norm)-centro)/((1-norm)-0.5)));
end