# 🚦 Semáforo Inteligente com Sensor Ultrassônico

Este projeto implementa um semáforo inteligente utilizando Arduino, capaz de alternar automaticamente entre as luzes vermelha e verde de acordo com a proximidade de um objeto detectada por um sensor ultrassônico.  
O objetivo é simular um sistema de controle de tráfego automatizado, onde a passagem é liberada (luz verde) apenas quando há detecção próxima de um veículo ou pedestre.


## Funcionalidade

- Quando não há objeto próximo, o LED vermelho** permanece aceso, indicando parada.  
- Quando um objeto é detectado a menos de 60 cm, o LED verde acende, liberando a passagem.  
- A leitura é feita continuamente pelo sensor ultrassônico HC-SR04, e a distância é exibida no*Monitor Serial.


## Componentes Utilizados

| Componente | Quantidade | Função |
|------------|------------|--------|
| Arduino Uno | 1 | Microcontrolador principal |
| LED Vermelho | 1 | Indica parada |
| LED Verde | 1 | Indica liberação |
| Resistores (220Ω) | 3 | Limitação de corrente dos LEDs |
| Sensor Ultrassônico HC-SR04 | 1 | Medição de distância |
| Jumpers | Vários | Conexões elétricas |
| Protoboard | 1 | Montagem do circuito |


## Esquema de Conexões

| Componente | Pino Arduino |
|------------|--------------|
| LED Vermelho | 13 |
| LED Verde | 10 |
| Trigger (HC-SR04) | 7 |
| Echo (HC-SR04) | 6 |


##  Código-Fonte

O código é estruturado em **Programação Orientada a Objetos (POO)**, utilizando uma **classe `Semaforo`** para organizar o controle dos LEDs.

```cpp
class Semaforo { 
  private:
    int ledVermelho;
    int ledVerde;

  public:
    Semaforo(int vm, int am, int vd) {
      ledVermelho = vm;
      ledVerde = vd;
    }

    void iniciar() {
      pinMode(ledVermelho, OUTPUT);
      pinMode(ledVerde, OUTPUT);
    }

    void vermelho() {
      digitalWrite(ledVermelho, HIGH);
      digitalWrite(ledVerde, LOW);
    }

    void verde() {
      digitalWrite(ledVermelho, LOW);
      digitalWrite(ledVerde, HIGH);
    }
};
```

A lógica principal mede a distância e altera o estado do semáforo:

```cpp
float medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracao = pulseIn(echoPin, HIGH);
  float distancia = duracao * 0.034 / 2;

  return distancia;
}

void loop() {
  float distancia = medirDistancia();
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if (distancia < 60) {
    semaforo.verde();
  } else {
    semaforo.vermelho();
  }
}
```

## Demonstração do Projeto

### Luz Vermelha (objeto distante)
Quando não há objeto próximo (distância > 60 cm), o semáforo permanece **vermelho**.

<img width="266" height="225" alt="vermelho" src="https://github.com/user-attachments/assets/c048738d-2bf1-4c9c-b4d4-8af834f25923" />



### Luz Verde (objeto próximo)
Quando um objeto se aproxima (distância < 60 cm), o semáforo muda para **verde**.

<img width="269" height="230" alt="verde" src="https://github.com/user-attachments/assets/e1eb8db7-0e92-42bb-ac9b-a5e1c825d53d" />



## Conceitos Envolvidos

- Programação Orientada a Objetos (classe Semaforo)
- Leitura de distância com o sensor ultrassônico
- Controle de LEDs via portas digitais
- Estrutura de decisão com if/else
- Serial Monitor para depuração


## Possíveis Melhorias

- Implementar o LED amarelo para transições.
- Adicionar temporizadores para simular tempos reais de semáforo.
- Exibir o status em um display LCD.
- Integrar comunicação com outros semáforos via rede (IoT).

## Autora
Nathália Pires de Figueredo
