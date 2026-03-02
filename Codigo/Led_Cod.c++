const int PINO_LED_R = 11;
const int PINO_LED_G = 10;
const int PINO_LED_B = 9;

const int PINO_SENSOR = A0;
const int LIMIAR_SOM = 999;
const unsigned long DEBOUNCE_DELAY = 200;

int estadoAtual = 0;
bool ultimoEstadoSensor = LOW;
unsigned long ultimoTempoDebounce = 0;

void setup() {
  pinMode(PINO_LED_R, OUTPUT);
  pinMode(PINO_LED_G, OUTPUT);
  pinMode(PINO_LED_B, OUTPUT);

  Serial.begin(9600);
  apagarLEDs();
}

void loop() {
  int valorSensor = analogRead(PINO_SENSOR);
  bool estadoSensor = valorSensor > LIMIAR_SOM;

  Serial.println(valorSensor);

  if (estadoSensor && !ultimoEstadoSensor && (millis() - ultimoTempoDebounce > DEBOUNCE_DELAY)) {
    ultimoTempoDebounce = millis();
    estadoAtual = (estadoAtual + 1) % 5;
    atualizarLEDs(estadoAtual);
  }
  ultimoEstadoSensor = estadoSensor;
}

void atualizarLEDs(int estado) {
  switch (estado) {
    case 0:
      setLEDs(HIGH, LOW, LOW);
      break;
    case 1:
      setLEDs(LOW, HIGH, LOW);
      break;
    case 2:
      setLEDs(LOW, LOW, HIGH);
      break;
    case 3:
      setLEDs(HIGH, LOW, HIGH);
      break;
    case 4:
    default:
      apagarLEDs();
      break;
  }
}

void setLEDs(bool r, bool g, bool b) {
  digitalWrite(PINO_LED_R, r);
  digitalWrite(PINO_LED_G, g);
  digitalWrite(PINO_LED_B, b);
}

void apagarLEDs() {
  setLEDs(LOW, LOW, LOW);
}
