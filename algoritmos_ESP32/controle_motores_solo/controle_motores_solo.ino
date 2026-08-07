HardwareSerial PixhawkSerial(2);  // Utilizar a UART2 do ESP32

// Pinos de comunicação com a Pixhawk
#define RXD2 22
#define TXD2 23

// Pinos Motores
int motor_esquerda_1_enable = 4;
int motor_esquerda_1_horario = 16;
int motor_esquerda_1_antihorario = 17;

int motor_esquerda_2_enable = 21;
int motor_esquerda_2_horario = 19;
int motor_esquerda_2_antihorario = 18;

int motor_direita_1_enable = 26;
int motor_direita_1_horario = 33;
int motor_direita_1_antihorario = 32;

int motor_direita_2_enable = 13;
int motor_direita_2_horario = 14;
int motor_direita_2_antihorario = 27;

// Propriedades do PWM
int freq = 1000;
int resolution = 8;

const byte START_BYTE = 0xAA;

enum EstadoDados{
  ESPERANDO_START,
  LENDO_HABILITADO,
  LENDO_VELOCIDADE,
  LENDO_DIRECAO,
  LENDO_CHECKSUM
};

EstadoDados estado = ESPERANDO_START;

byte habilitado = 0;
byte velocidade = 0;
byte direcao = 1;
byte checksum_recebido = 0;

unsigned long ultimoPacoteValido = 0;
const unsigned long TIMEOUT_COMUNICACAO = 500;

void setup() {

  pinMode(motor_esquerda_1_enable, OUTPUT);
  pinMode(motor_esquerda_1_horario, OUTPUT);
  pinMode(motor_esquerda_1_antihorario, OUTPUT);

  pinMode(motor_esquerda_2_enable, OUTPUT);
  pinMode(motor_esquerda_2_horario, OUTPUT);
  pinMode(motor_esquerda_2_antihorario, OUTPUT);

  pinMode(motor_direita_1_enable, OUTPUT);
  pinMode(motor_direita_1_horario, OUTPUT);
  pinMode(motor_direita_1_antihorario, OUTPUT);

  pinMode(motor_direita_2_enable, OUTPUT);
  pinMode(motor_direita_2_horario, OUTPUT);
  pinMode(motor_direita_2_antihorario, OUTPUT);

  PixhawkSerial.begin(  // Inicia a comunicação serial PixhawkSerial
    57600,              // velocidade de comunicação (baudrate) configurada no parâmetro SERIAL2_BAUD da Pixhawk
    SERIAL_8N1,         // formato dos dados seriais
    RXD2,               // pino RX
    TXD2                // Pino TX
  );

  ledcAttach(motor_esquerda_1_enable, freq, resolution);
  ledcAttach(motor_esquerda_2_enable, freq, resolution);
  ledcAttach(motor_direita_1_enable, freq, resolution);
  ledcAttach(motor_direita_2_enable, freq, resolution);

  Serial.begin(115200);

}

void loop() {
  
  receberPacote();

  if (millis() - ultimoPacoteValido > TIMEOUT_COMUNICACAO) {
    parar();
  }

}

void receberPacote() {
  while (PixhawkSerial.available()) {
    byte b = PixhawkSerial.read();

    switch (estado) {

      case ESPERANDO_START:
        if (b == START_BYTE) {
          estado = LENDO_HABILITADO;
        }
        break;

      case LENDO_HABILITADO:
        habilitado = b;
        estado = LENDO_VELOCIDADE;
        break;

      case LENDO_VELOCIDADE:
        velocidade = b;
        estado = LENDO_DIRECAO;
        break;

      case LENDO_DIRECAO:
        direcao = b;
        estado = LENDO_CHECKSUM;
        break;

      case LENDO_CHECKSUM:
        checksum_recebido = b;

        byte checksum_calculado;
        checksum_calculado = (habilitado + velocidade + direcao ) % 256;

        if (checksum_recebido == checksum_calculado) {
          ultimoPacoteValido = millis();
          executarComando();
        } else {
          Serial.println("Pacote corrompido");
        }

        estado = ESPERANDO_START;
        break;
    }
  }
}

void executarComando() {
  Serial.print("Habilitado: ");
  Serial.print(habilitado);

  Serial.print(" | Velocidade: ");
  Serial.print(velocidade);

  Serial.print(" | Direcao: ");
  Serial.println(direcao);

  if (habilitado == 0) {
    parar();
    return;
  }

  int pwmBase = 0;

  if (velocidade == 0) {
    pwmBase = 0;
  }
  else if (velocidade == 1){
    pwmBase = 90;
  } 
  else if (velocidade == 2) {
    pwmBase = 180;
  } 
  else if (velocidade == 3) {
    pwmBase = 250;
  } 
  else {
    pwmBase = 0;
  }

  if (direcao == 0) {
    esquerda(pwmBase);
  } 
  else if (direcao == 2) {
    frente(pwmBase);
  }
  else{
    direita(pwmBase);
  }
}


void frente(int pwmBase){

  ledcWrite(motor_esquerda_1_enable, pwmBase);
  digitalWrite(motor_esquerda_1_horario, HIGH);
  digitalWrite(motor_esquerda_1_antihorario, LOW);

  ledcWrite(motor_esquerda_2_enable, pwmBase);
  digitalWrite(motor_esquerda_2_horario, HIGH);
  digitalWrite(motor_esquerda_2_antihorario, LOW);

  ledcWrite(motor_direita_1_enable, pwmBase);
  digitalWrite(motor_direita_1_horario, HIGH);
  digitalWrite(motor_direita_1_antihorario, LOW);

  ledcWrite(motor_direita_2_enable, pwmBase);
  digitalWrite(motor_direita_2_horario, HIGH);
  digitalWrite(motor_direita_2_antihorario, LOW);

}

void direita(int pwmBase){

  ledcWrite(motor_esquerda_1_enable, pwmBase);
  digitalWrite(motor_esquerda_1_horario, HIGH);
  digitalWrite(motor_esquerda_1_antihorario, LOW);

  ledcWrite(motor_esquerda_2_enable, pwmBase);
  digitalWrite(motor_esquerda_2_horario, HIGH);
  digitalWrite(motor_esquerda_2_antihorario, LOW);

  ledcWrite(motor_direita_1_enable, pwmBase);
  digitalWrite(motor_direita_1_horario, LOW);
  digitalWrite(motor_direita_1_antihorario, HIGH);

  ledcWrite(motor_direita_2_enable, pwmBase);
  digitalWrite(motor_direita_2_horario, LOW);
  digitalWrite(motor_direita_2_antihorario, HIGH);
}


void esquerda(int pwmBase){

  ledcWrite(motor_esquerda_1_enable, pwmBase);
  digitalWrite(motor_esquerda_1_horario, LOW);
  digitalWrite(motor_esquerda_1_antihorario, HIGH);

  ledcWrite(motor_esquerda_2_enable, pwmBase);
  digitalWrite(motor_esquerda_2_horario, LOW);
  digitalWrite(motor_esquerda_2_antihorario, HIGH);

  ledcWrite(motor_direita_1_enable, pwmBase);
  digitalWrite(motor_direita_1_horario, HIGH);
  digitalWrite(motor_direita_1_antihorario, LOW);

  ledcWrite(motor_direita_2_enable, pwmBase);
  digitalWrite(motor_direita_2_horario, HIGH);
  digitalWrite(motor_direita_2_antihorario, LOW);
}




