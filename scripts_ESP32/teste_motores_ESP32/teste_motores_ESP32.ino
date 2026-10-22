
// Pinos dos motores do lado esquerdo
const int motor_esquerda_1_enable = 4;
const int motor_esquerda_1_horario = 17;
const int motor_esquerda_1_antihorario = 16;

const int motor_esquerda_2_enable = 21;
const int motor_esquerda_2_antihorario = 18;
const int motor_esquerda_2_horario = 19;

// Pinos dos motores do lado direito
const int motor_direita_1_enable = 32;
const int motor_direita_1_antihorario = 33;
const int motor_direita_1_horario = 26;

const int motor_direita_2_enable = 13;
const int motor_direita_2_antihorario = 27;
const int motor_direita_2_horario = 14;


// Propriedades do sinal PWM
const int freq = 1000;
const int resolution = 8;

void setup() {

  Serial.begin(115200);

  // Configuração dos pinos dos motores do lado esquerdo
  pinMode(motor_esquerda_1_enable, OUTPUT);
  pinMode(motor_esquerda_1_horario, OUTPUT);
  pinMode(motor_esquerda_1_antihorario, OUTPUT);

  pinMode(motor_esquerda_2_enable, OUTPUT);
  pinMode(motor_esquerda_2_horario, OUTPUT);
  pinMode(motor_esquerda_2_antihorario, OUTPUT);

  // Configuração dos pinos dos motores do lado direito
  pinMode(motor_direita_1_enable, OUTPUT);
  pinMode(motor_direita_1_horario, OUTPUT);
  pinMode(motor_direita_1_antihorario, OUTPUT);

  pinMode(motor_direita_2_enable, OUTPUT);
  pinMode(motor_direita_2_horario, OUTPUT);
  pinMode(motor_direita_2_antihorario, OUTPUT);

  // Configuração do PWM nos pinos enable
  ledcAttach(motor_esquerda_1_enable, freq, resolution);
  ledcAttach(motor_esquerda_2_enable, freq, resolution);
  ledcAttach(motor_direita_1_enable, freq, resolution);
  ledcAttach(motor_direita_2_enable, freq, resolution);

  parar();
}


void loop() {

      frente(255);
        delay(2000);

      direita(255);
        delay(2000);

      esquerda(255);
        delay(2000);

      tras(255);
        delay(2000);

}

void frente(int pwmBase) {

  // Motores do lado esquerdo para frente
  ledcWrite(motor_esquerda_1_enable, pwmBase);
  digitalWrite(motor_esquerda_1_horario, HIGH);
  digitalWrite(motor_esquerda_1_antihorario, LOW);

  ledcWrite(motor_esquerda_2_enable, pwmBase);
  digitalWrite(motor_esquerda_2_horario, HIGH);
  digitalWrite(motor_esquerda_2_antihorario, LOW);

  // Motores do lado direito para frente
  ledcWrite(motor_direita_1_enable, pwmBase);
  digitalWrite(motor_direita_1_horario, HIGH);
  digitalWrite(motor_direita_1_antihorario, LOW);

  ledcWrite(motor_direita_2_enable, pwmBase);
  digitalWrite(motor_direita_2_horario, HIGH);
  digitalWrite(motor_direita_2_antihorario, LOW);
}

void tras(int pwmBase) {

  // Motores do lado esquerdo para frente
  ledcWrite(motor_esquerda_1_enable, pwmBase);
  digitalWrite(motor_esquerda_1_antihorario, HIGH);
  digitalWrite(motor_esquerda_1_horario, LOW);

  ledcWrite(motor_esquerda_2_enable, pwmBase);
  digitalWrite(motor_esquerda_2_antihorario, HIGH);
  digitalWrite(motor_esquerda_2_horario, LOW);

  // Motores do lado direito para frente
  ledcWrite(motor_direita_1_enable, pwmBase);
  digitalWrite(motor_direita_1_antihorario, HIGH);
  digitalWrite(motor_direita_1_horario, LOW);

  ledcWrite(motor_direita_2_enable, pwmBase);
  digitalWrite(motor_direita_2_antihorario, HIGH);
  digitalWrite(motor_direita_2_horario, LOW);
}

void direita(int pwmBase) {

  // Motores do lado esquerdo para frente
  ledcWrite(motor_esquerda_1_enable, pwmBase);
  digitalWrite(motor_esquerda_1_horario, HIGH);
  digitalWrite(motor_esquerda_1_antihorario, LOW);

  ledcWrite(motor_esquerda_2_enable, pwmBase);
  digitalWrite(motor_esquerda_2_horario, HIGH);
  digitalWrite(motor_esquerda_2_antihorario, LOW);

  // Motores do lado direito no sentido oposto
  ledcWrite(motor_direita_1_enable, pwmBase);
  digitalWrite(motor_direita_1_horario, LOW);
  digitalWrite(motor_direita_1_antihorario, HIGH);

  ledcWrite(motor_direita_2_enable, pwmBase);
  digitalWrite(motor_direita_2_horario, LOW);
  digitalWrite(motor_direita_2_antihorario, HIGH);
}


void esquerda(int pwmBase) {

  // Motores do lado esquerdo no sentido oposto
  ledcWrite(motor_esquerda_1_enable, pwmBase);
  digitalWrite(motor_esquerda_1_horario, LOW);
  digitalWrite(motor_esquerda_1_antihorario, HIGH);

  ledcWrite(motor_esquerda_2_enable, pwmBase);
  digitalWrite(motor_esquerda_2_horario, LOW);
  digitalWrite(motor_esquerda_2_antihorario, HIGH);

  // Motores do lado direito para frente
  ledcWrite(motor_direita_1_enable, pwmBase);
  digitalWrite(motor_direita_1_horario, HIGH);
  digitalWrite(motor_direita_1_antihorario, LOW);

  ledcWrite(motor_direita_2_enable, pwmBase);
  digitalWrite(motor_direita_2_horario, HIGH);
  digitalWrite(motor_direita_2_antihorario, LOW);
}


void parar() {

  // Para os motores do lado esquerdo
  ledcWrite(motor_esquerda_1_enable, 0);
  digitalWrite(motor_esquerda_1_horario, LOW);
  digitalWrite(motor_esquerda_1_antihorario, LOW);

  ledcWrite(motor_esquerda_2_enable, 0);
  digitalWrite(motor_esquerda_2_horario, LOW);
  digitalWrite(motor_esquerda_2_antihorario, LOW);

  // Para os motores do lado direito
  ledcWrite(motor_direita_1_enable, 0);
  digitalWrite(motor_direita_1_horario, LOW);
  digitalWrite(motor_direita_1_antihorario, LOW);

  ledcWrite(motor_direita_2_enable, 0);
  digitalWrite(motor_direita_2_horario, LOW);
  digitalWrite(motor_direita_2_antihorario, LOW);
}
