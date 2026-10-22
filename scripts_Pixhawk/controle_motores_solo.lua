local port = serial:find_serial(0)

if not port then
    gcs:send_text(0, "Erro de comunicacao")
    return
end

port:begin(57600)
port:set_flow_control(0)

local contador_msg = 0


function write_byte(b)
    port:write(b)
end


function send_packet(habilitado, velocidade, direcao)

    local start = 0xAA

    local checksum =
        (habilitado + velocidade + direcao) % 256

    write_byte(start)
    write_byte(habilitado)
    write_byte(velocidade)
    write_byte(direcao)
    write_byte(checksum)
end


function update()

    local ch1 = rc:get_pwm(1)
    local ch3 = rc:get_pwm(3)
    local ch6 = rc:get_pwm(6)


    -- Verifica se os canais estao sendo recebidos
    if not ch1 or not ch3 or not ch6 then

        gcs:send_text(6, "RC sem sinal")

        return update, 500
    end


    --------------------------------------------------
    -- HABILITACAO PELO CANAL 6
    --------------------------------------------------

    local habilitado = 0

    if ch6 > 1500 then
        habilitado = 1
    else
        habilitado = 0
    end


    --------------------------------------------------
    -- MENSAGEM DE DIAGNOSTICO DO CH6
    -- Aparece aproximadamente uma vez por segundo
    --------------------------------------------------

    contador_msg = contador_msg + 1

    if contador_msg >= 5 then

        gcs:send_text(
            6,
            "CH6 = " .. tostring(ch6) ..
            " | Habilitado = " .. tostring(habilitado)
        )

        contador_msg = 0
    end


    --------------------------------------------------
    -- VELOCIDADE - CH3
    --------------------------------------------------

    local velocidade = 0

    if ch3 < 1050 then

        velocidade = 0

    elseif ch3 < 1200 then

        velocidade = 1

    elseif ch3 < 1500 then

        velocidade = 2

    elseif ch3 < 1700 then

        velocidade = 3

    else

        velocidade = 4

    end


    --------------------------------------------------
    -- DIRECAO - CH1
    --------------------------------------------------

    local direcao = 1

    if ch1 < 1300 then

        direcao = 0

    elseif ch1 > 1700 then

        direcao = 2

    else

        direcao = 1

    end


    --------------------------------------------------
    -- ENVIA PARA O ESP32
    --------------------------------------------------

    send_packet(
        habilitado,
        velocidade,
        direcao
    )


    return update, 200
end


return update()