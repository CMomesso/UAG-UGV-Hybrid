clc;
clear;
close all;

%% Arquivos

arquivo_antes_com_carga  = "FFT_sem_notch_com_carga.BIN";
arquivo_depois_com_carga = "FFT_com_notch_com_carga.BIN";

arquivo_antes_sem_carga  = "FFT_sem_notch_sem_carga.BIN";
arquivo_depois_sem_carga = "FFT_com_notch_sem_carga.BIN";

%% Leitura dos dados de altitude

dados_antes_com_carga = processa_altitude(arquivo_antes_com_carga);
dados_depois_com_carga = processa_altitude(arquivo_depois_com_carga);

dados_antes_sem_carga = processa_altitude(arquivo_antes_sem_carga);
dados_depois_sem_carga = processa_altitude(arquivo_depois_sem_carga);

%% Resultados 

fprintf("\n--- VOO SEM CARGA: CONFIGURAÇÃO BASE ---\n");
fprintf("Desvio médio absoluto = %.4f m\n", ...
    dados_antes_sem_carga.desvio_medio_abs);
fprintf("Desvio médio com sinal = %.4f m\n", ...
    dados_antes_sem_carga.desvio_medio);
fprintf("Desvio padrão do erro = %.4f m\n", ...
    dados_antes_sem_carga.desvio_padrao);

fprintf("\n--- VOO SEM CARGA: APÓS O AJUSTE DOS FILTROS ---\n");
fprintf("Desvio médio absoluto = %.4f m\n", ...
    dados_depois_sem_carga.desvio_medio_abs);
fprintf("Desvio médio com sinal = %.4f m\n", ...
    dados_depois_sem_carga.desvio_medio);
fprintf("Desvio padrão do erro = %.4f m\n", ...
    dados_depois_sem_carga.desvio_padrao);

fprintf("\n--- VOO COM CARGA: CONFIGURAÇÃO BASE ---\n");
fprintf("Desvio médio absoluto = %.4f m\n", ...
    dados_antes_com_carga.desvio_medio_abs);
fprintf("Desvio médio com sinal = %.4f m\n", ...
    dados_antes_com_carga.desvio_medio);
fprintf("Desvio padrão do erro = %.4f m\n", ...
    dados_antes_com_carga.desvio_padrao);

fprintf("\n--- VOO COM CARGA: APÓS O AJUSTE DOS FILTROS ---\n");
fprintf("Desvio médio absoluto = %.4f m\n", ...
    dados_depois_com_carga.desvio_medio_abs);
fprintf("Desvio médio com sinal = %.4f m\n", ...
    dados_depois_com_carga.desvio_medio);
fprintf("Desvio padrão do erro = %.4f m\n", ...
    dados_depois_com_carga.desvio_padrao);

%% Figura com quatro subplots

figure(1);


subplot(2,2,1);

plot(dados_antes_sem_carga.t, ...
     dados_antes_sem_carga.DSAlt, ...
     "LineWidth", 1.3);

hold on;

plot(dados_antes_sem_carga.t, ...
     dados_antes_sem_carga.SAlt, ...
     "LineWidth", 1.3);

grid on;
xlabel("Tempo [s]");
ylabel("Altitude [m]");
ylim([0 2]);
title("(a) Sem carga — configuração base");
legend("Altitude de referência", ...
       "Altitude medida", ...
       "Location", "best");


subplot(2,2,2);

plot(dados_depois_sem_carga.t, ...
     dados_depois_sem_carga.DSAlt, ...
     "LineWidth", 1.3);

hold on;

plot(dados_depois_sem_carga.t, ...
     dados_depois_sem_carga.SAlt, ...
     "LineWidth", 1.3);

grid on;
xlabel("Tempo [s]");
ylabel("Altitude [m]");
ylim([0 2]);
title("(b) Sem carga — após o ajuste dos filtros");
legend("Altitude de referência", ...
       "Altitude medida", ...
       "Location", "best");


subplot(2,2,3);

plot(dados_antes_com_carga.t, ...
     dados_antes_com_carga.DSAlt, ...
     "LineWidth", 1.3);

hold on;

plot(dados_antes_com_carga.t, ...
     dados_antes_com_carga.SAlt, ...
     "LineWidth", 1.3);

grid on;
xlabel("Tempo [s]");
ylabel("Altitude [m]");
ylim([0 2]);
title("(c) Com carga — configuração base");
legend("Altitude de referência", ...
       "Altitude medida", ...
       "Location", "best");


subplot(2,2,4);

plot(dados_depois_com_carga.t, ...
     dados_depois_com_carga.DSAlt, ...
     "LineWidth", 1.3);

hold on;

plot(dados_depois_com_carga.t, ...
     dados_depois_com_carga.SAlt, ...
     "LineWidth", 1.3);

grid on;
xlabel("Tempo [s]");
ylabel("Altitude [m]");
ylim([0 2]);
title("(d) Com carga — após o ajuste dos filtros");
legend("Altitude de referência", ...
       "Altitude medida", ...
       "Location", "best");

sgtitle("Resposta em altitude antes e após o ajuste dos filtros");


function dados = processa_altitude(nome_arquivo)

    rawdata = ardupilotreader(nome_arquivo);

    ctunMsg = readMessages(rawdata, MessageName="CTUN");
    ctun = ctunMsg.MsgData{1};

    t = seconds(ctun.TimeUS - ctun.TimeUS(1));

    DSAlt = ctun.DSAlt;  % Altitude de referência
    SAlt = ctun.SAlt;    % Altitude medida/estimada

    erro = SAlt - DSAlt;

    dados.t = t;
    dados.DSAlt = DSAlt;
    dados.SAlt = SAlt;
    dados.erro = erro;

    dados.desvio_medio_abs = mean(abs(erro), "omitnan");
    dados.desvio_medio = mean(erro, "omitnan");
    dados.desvio_padrao = std(erro, "omitnan");

end