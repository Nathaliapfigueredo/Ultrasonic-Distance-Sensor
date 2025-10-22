class Semaforo {
  private:
    int ledVermelho;
    int ledAmarelo;
    int ledVerde;

  public:
    Semaforo(int vm, int am, int vd) {
      ledVermelho = vm;
      ledAmarelo = am;
      ledVerde = vd;
    }

    void iniciar() {
      pinMode(ledVermelho, OUTPUT);
      pinMode(ledAmarelo, OUTPUT);
      pinMode(ledVerde, OUTPUT);
    }

    void vermelho() {
      digitalWrite(ledVermelho, HIGH);
      digitalWrite(ledAmarelo, LOW);
      digitalWrite(ledVerde, LOW);
    }

    void verde() {
      digitalWrite(ledVermelho, LOW);
      digitalWrite(ledAmarelo, LOW);
      digitalWrite(ledVerde, HIGH);
    }
};

//Cria o objeto semáforo
Semaforo semaforo(13, 12, 10);

//Pinos do sensor ultrassônico
const int trigPin = 7;
const int echoPin = 6;

void setup() {
  Serial.begin(9600);
  semaforo.iniciar();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Começa com a luz vermelha acesa
  semaforo.vermelho();
}

// Mede distância
float medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracao = pulseIn(echoPin, HIGH);
  float distancia = duracao * 0.034 / 2; // velocidade do som: 0.034 cm/µs

  return distancia;
}

void loop() {
  float distancia = medirDistancia();
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  //Se um objeto estiver a menos de 10 cm, fica verde
  if (distancia < 60) {
    semaforo.verde();
  } 
  //Se não, fica vermelho
  else {
    semaforo.vermelho();
  }
}
